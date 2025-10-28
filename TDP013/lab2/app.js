function getDate() {
    const date = new Date();
    let min = String(date.getMinutes());
    if (min.length == 1) {min = "0" + min}
    return "Posted at " + date.getFullYear() + "-" + date.getMonth() + "-" +  date.getDate() + " " + date.getHours() + ":" + min;
}

function addMessages(msg, author, date, id, read) {
    const divBox = document.getElementById("divBox");
    const divMsg = document.createElement("div");
    const contentBox = document.createElement("div");
    contentBox.class = "contentBox";
    divMsg.className = "container-fluid card bg-secondary mb-3 divMsg";
    divMsg.setAttribute("style", "max-width: 90%; border: solid; width: 50%; height: 9rem");

    const textContent = document.createElement("p");
    textContent.textContent = msg;
    textContent.class = "text";

    const checkBox = document.createElement("input");
    checkBox.setAttribute("style", "margin-top: 1rem; width: 3rem; height: 3rem;");
    checkBox.class = "form-check-input checkBox";
    checkBox.type = "checkbox";
    checkBox.id = id == undefined ? new Date() : id;
    checkBox.checked = read ? true : false;
    checkBox.addEventListener("click", () => checkRead(checkBox));

    const nameContent = document.createElement("p");
    nameContent.textContent = author == undefined ? "Jakob Coolberg" : author;
    nameContent.class = "nameContent";
    
    const dateContent = document.createElement("p");
    dateContent.textContent = date == undefined ? getDate() : date;
    dateContent.class = "date";

    if (id == undefined)
        setCookie(checkBox.id, nameContent.textContent, msg, checkBox.checked, dateContent.textContent)

    contentBox.appendChild(nameContent);
    contentBox.appendChild(textContent);
    contentBox.appendChild(dateContent);
    
    divMsg.appendChild(contentBox);
    divMsg.appendChild(checkBox);
    if (read){
        checkRead(checkBox);
    }
    
    divBox.insertBefore(divMsg, divBox.children[0]);
}

function checkMessage() {
    var message = document.getElementById("post").value;
    if (message.length == 0 || message.length > 140){
        document.getElementById("errorMessage").innerHTML = "Meddelanden måste innehålla 1 - 140 tecken!";
    }
    else{
        if (document.getElementById("errorMessage").textContent){
            document.getElementById("errorMessage").innerHTML = null;
        }
        addMessages(message);
    }
}

function checkRead(checkBox) {
    var card = checkBox.closest(".card");

    const message = card.children[0].children[1].innerHTML;
    const date = card.children[0].children[2].innerHTML;
    const name = card.children[0].children[0].innerHTML;
    if (checkBox.checked) {
        card.style.borderColor = "green";
        document.cookie = `${checkBox.id}=${encodeURIComponent(`sender=${name}|message=${message}|read=${true}|date=${date}`)}; path=/`;
    }
    else {
        document.cookie = `${checkBox.id}=${encodeURIComponent(`sender=${name}|message=${message}|read=${false}|date=${date}`)}; path=/`;
        card.style.borderColor = "black";
    }
}

function setCookie(id, cname, cmsg, cread, cdate){
    document.cookie = `${id}=${encodeURIComponent(`sender=${cname}|message=${cmsg}|read=${cread}|date=${cdate}`)}; path=/`;
}

function loadMessages(){
    let cookies = decodeURIComponent(document.cookie);
    let cArray = cookies.split("; ");
    cArray.sort();
    for (i in cArray){
        const id = cArray[i].split("|")[0].split("=")[0]
        const author = cArray[i].split("|")[0].split("=")[2]
        const message = cArray[i].split("|")[1].split("=")[1]
        const read = cArray[i].split("|")[2].split("=")[1]
        const date = cArray[i].split("|")[3].split("=")[1]
        addMessages(message, author, date, id, read == 'true')
    }
}
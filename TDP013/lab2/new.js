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
    checkBox.id = id;
    checkBox.checked = read ? true : false;
    checkBox.addEventListener("click", () => checkRead(checkBox));

    const nameContent = document.createElement("p");
    nameContent.textContent = author == undefined ? "Jakob Coolberg" : author;
    nameContent.class = "nameContent";
    
    const dateContent = document.createElement("p");
    dateContent.textContent = date == undefined ? getDate() : date;
    dateContent.class = "date";
    
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
        postUsingXMLHttpRequest(message);
    }
}

function checkRead(checkBox) {
    var card = checkBox.closest(".card");
    if (checkBox.checked) {
        card.style.borderColor = "green";
        patchUsingXMLHttpRequest(true, checkBox.id)
    }
    else {
        card.style.borderColor = "black";
        patchUsingXMLHttpRequest(false, checkBox.id)

    }
}

function postUsingXMLHttpRequest(value){
    let xhttp = new XMLHttpRequest();
    xhttp.open('POST', '/messages', true);
    xhttp.onload = () => {
        if (xhttp.status == 201) {
            let id = JSON.parse(xhttp.response).insertedId
            getMessageById(id);
        }
    };
    xhttp.setRequestHeader('Content-Type', 'application/json');
    xhttp.send(JSON.stringify({ author: "Elias", message: value, date: "typ nu", read: false }));
}

function loadDoc() {
    //console.log("Sidan laddades");
  const xhttp = new XMLHttpRequest();
  xhttp.open("GET", "/messages", true)
  xhttp.onload = () => {
    if (xhttp.status == 200) {
        let messages = JSON.parse(xhttp.response)
        messages.forEach(messages => {
            addMessages(messages.message, messages.author, messages.date, messages._id, messages.read)
        });
    }
  }
  xhttp.send();
}

function getMessageById(id) {
  const xhttp = new XMLHttpRequest();
  xhttp.open("GET", `/messages/${id}`, true)
  xhttp.onload = () => {
    if (xhttp.status == 200) {
        let message = JSON.parse(xhttp.response)
        addMessages(message.message, message.author, message.date, message._id, message.read)
    }
  }
  xhttp.send();
}

function patchUsingXMLHttpRequest(value, id){
    let xhttp = new XMLHttpRequest();
    xhttp.open('PATCH', `/messages/${id}`, true);
    //xhttp.onload = () => {
    //    if (xhttp.status == 200) {
    //        
    //    }
    //};
    xhttp.setRequestHeader('Content-Type', 'application/json');
    xhttp.send(JSON.stringify({ read: value }));
}

if (typeof module !== "undefined") {
  module.exports = { postUsingXMLHttpRequest, patchUsingXMLHttpRequest, getMessageById, loadDoc };
}
#6a
def math(n):
    summa = 0
    for tal in range(1, 513):
        summa = n(summa, tal)
        if summa == 0:
            summa = 1

x = lambda a, b: a*b
y = lambda a, b: a+b

#math(y)
#math(x)

#6b
db = [{'name': 'Jakob', 'position': 'assistant'}, {'name': 'Åke', 'position': 'assistant'}, {'name': 'Ola', 'position': 'examiner'}, {'name': 'Henrik', 'position': 'assistant'}, ]

def dbsearch(x, y ,z):
    results = []
    for dicts in x:
        for key, value in dicts.items():
            if key == y and value == z:
                results.append(dicts)
    return results
    
#print(dbsearch(db, 'position', 'assistant'))

#6c
haystack = 'Can you find the needle in this haystack?'.split()
def contains(a, b):
    for items in b:
        if items == a:
            return True
    
    return False

#print(contains('needle', haystack))

#6d
def linear_search(x, y, z=lambda i, y: i == y):
    for i in x:
       if z(i, y):
           return i

#print(linear_search(haystack, 'needle', lambda i, y: i == y))

#6e
def binary_search(haystack, y, z=lambda i, y: i[0] > y[0]):
    start_point = len(haystack) // 2
    while True:
        start = haystack[start_point]
        if z(start, y):
            ny_punkt = (len(haystack) - haystack.index(start)) // 2
            start_point = haystack.index(start) - ny_punkt
            #print(f"{start} mindre")
            continue
        elif z(y, start):
            ny_punkt = (len(haystack) - haystack.index(start)) // 2
            start_point = haystack.index(start) + ny_punkt
            #print(f"{start} större")
            continue
        else:
            return y
    
#print(binary_search(sorted(haystack), 'needle'))

insertion = [2, 5, 7, 5, 3, 2, 4, 8, 1, 6, 10, 5, 3, 4]
#6f
def insertion_sort(insertion, z=lambda i, y: i > y):
    try:
        for i in insertion:
            next = insertion.index(i)
            if z(i, insertion[next+1]):
                insert_num = insertion.pop(next+1)
                for old_numbers in reversed(insertion[:next]):
                    past = insertion.index(old_numbers)
                    if insertion[past] == insertion[past+1]:
                        past += 1
                        if z(insert_num, old_numbers) or old_numbers == insert_num:
                            insertion.insert(past+1, insert_num)
                            break
                    elif z(insert_num, old_numbers) or old_numbers == insert_num:
                        insertion.insert(past+1, insert_num)
                        break
    except IndexError:
        return insertion
   
#print(insertion_sort(insertion, z=lambda i, y: i > y))

#6e
insertion = [2, 5, 7, 5, 3, 2, 4, 8, 1, 6, 10, 5, 3, 4]

def partition(insertion, start, end, z=lambda i, y: i > y):
    pivot = insertion[end]
    behind_pivot = end
    tal = start
    while start < end:
        if z(insertion[tal], pivot) or pivot == insertion[tal]:
            all_num = insertion.pop(tal)
            insertion.insert(behind_pivot, all_num)
            behind_pivot -= 1
            start += 1
        elif z(pivot, insertion[tal]):
            tal += 1
            start += 1
    return behind_pivot

def quicksort(insertion, start, end):
    if start < end:
        pivot = partition(insertion, start, end, z=lambda i, y: i > y)
        quicksort(insertion, start, pivot-1)
        quicksort(insertion, pivot+1, end)
    return insertion

#print(quicksort(insertion, 0, len(insertion)-1))



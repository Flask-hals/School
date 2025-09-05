#jakno825
#thosj050

def nested_pairs(elements):
    if elements == 1:
        yield ()
    else:
        for pairs in range(1, elements):
            for left in nested_pairs(pairs):
                for right in nested_pairs(elements-pairs):
                    yield (left, right)
        

#for pairs in nested_pairs(3):
#    print(pairs)

#------------------ Assignment 2 ----------------------

def count_nested_pairs(elements):
    if elements == 1:
        return 1
    sum = 0
    for pairs in range(1, elements):
        sum += count_nested_pairs(pairs) * count_nested_pairs(elements-pairs)
    return sum

#print(count_nested_pairs(4))

#------------------ Assignment 3 ----------------------

dict = {}

def count_nested_pairs_memoized(elements):
    if elements in dict.keys():
        return dict[elements]
    elif elements == 1:
        return 1
    sum = 0
    for pairs in range(1, elements):
        sum += count_nested_pairs_memoized(pairs) * count_nested_pairs_memoized(elements-pairs)
        dict[elements] = sum
    return sum

#print(count_nested_pairs_memoized(4))
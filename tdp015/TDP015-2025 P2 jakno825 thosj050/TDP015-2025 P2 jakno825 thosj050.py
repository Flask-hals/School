# jakno825
# thosj050
# TDP015 Programming Assignment 2
# Logic

import itertools


class Exp(object):
    """A Boolean expression.

    A Boolean expression is represented in terms of a *reserved symbol* (a
    string) and a list of *subexpressions* (instances of the class `Exp`).
    The reserved symbol is a unique name for the specific type of
    expression that an instance of the class represents. For example, the
    constant `True` uses the reserved symbol `1`, and logical and uses `∧`
    (the Unicode symbol for conjunction). The reserved symbol for a
    variable is its name, such as `x` or `y`.

    Attributes:
        sym: The reserved symbol of the expression (a string).
        sexps: The list of subexpressions (instances of the class `Exp`).
    """

    def __init__(self, sym, *sexps):
        """Constructs a new expression.

        Args:
            sym: The reserved symbol for this expression.
            sexps: The list of subexpressions.
        """
        self.sym = sym
        self.sexps = sexps

    def value(self, assignment):
        """Returns the value of this expression under the specified truth
        assignment.

        Args:
            assignment: A truth assignment, represented as a dictionary
            that maps variable names to truth values.

        Returns:
            The value of this expression under the specified truth
            assignment: either `True` or `False`.
        """
        raise ValueError()

    def variables(self):
        """Returns the (names of the) variables in this expression.

        Returns:
           The names of the variables in this expression, as a set.
        """
        variables = set()
        for sexp in self.sexps:
            variables |= sexp.variables()
        return variables


class Var(Exp):
    """A variable."""

    def __init__(self, sym):
        super().__init__(sym)

    def value(self, assignment):
        assert len(self.sexps) == 0
        return assignment[self.sym]

    def variables(self):
        assert len(self.sexps) == 0
        return {self.sym}


class Nega(Exp):
    """Logical not."""
    
    # TODO: Complete this class
    def __init__(self, sexp):
        super().__init__('!', sexp)

    def value(self, assignment):
        assert len(self.sexps) == 1
        return not self.sexps[0].value(assignment)



class Conj(Exp):
    """Logical and."""

    def __init__(self, sexp1, sexp2):
        super().__init__('∧', sexp1, sexp2)

    def value(self, assignment):
        assert len(self.sexps) == 2
        return \
            self.sexps[0].value(assignment) and \
            self.sexps[1].value(assignment)


class Disj(Exp):
    """Logical or."""

    # TODO: Complete this class
    def __init__(self, sexp1, sexp2):
        super().__init__('v', sexp1, sexp2)

    def value(self, assignment):
        assert len(self.sexps) == 2
        return \
            self.sexps[0].value(assignment) or \
            self.sexps[1].value(assignment)



class Impl(Exp):
    """Logical implication."""
    # TODO: Complete this class
    def __init__(self, sexp1, sexp2):
        super().__init__('->', sexp1, sexp2)

    def value(self, assignment):
        assert len(self.sexps) == 2
        if self.sexps[0].value(assignment) == True and self.sexps[1].value(assignment) == False:
            return False 
        else: 
            return True


class Equi(Exp):
    """Logical equivalence."""

    # TODO: Complete this class
    def __init__(self, sexp1, sexp2):
        super().__init__('<->', sexp1, sexp2)
    def value(self, assignment):
        assert len(self.sexps) == 2
        return self.sexps[0].value(assignment) == self.sexps[1].value(assignment)


def assignments(variables):
    """Yields all truth assignments to the specified variables.

    Args:
        variables: A set of variable names.

    Yields:
        All truth assignments to the specified variables. A truth
        assignment is represented as a dictionary mapping variable names to
        truth values. Example:

        {'x': True, 'y': False}
    """
    
    #TODO: Complete this function. Use the itertools module!
    exp = []
   
    for instance in itertools.product([0, 1], repeat=len(variables)):
        exp.append(dict(zip(variables, instance)))

    return exp



def satisfiable(exp):
    """Tests whether the specified expression is satisfiable.

    An expression is satisfiable if there is a truth assignment to its
    variables that makes the expression evaluate to true.

    Args:
        exp: A Boolean expression.

    Returns:
        A truth assignment that makes the specified expression evaluate to
        true, or False in case there does not exist such an assignment.
        A truth assignment is represented as a dictionary mapping variable
        names to truth values.
    """
    # TODO: Complete this function

    varNames = exp.variables()

    for i in assignments(varNames):
        if exp.value(i):
            return True
    
    return False

    


def tautology(exp):
    """Tests whether the specified expression is a tautology.

    An expression is a tautology if it evaluates to true under all
    truth assignments to its variables.

    Args:
        exp: A Boolean expression.

    Returns:
        True if the specified expression is a tautology, False otherwise.
    """
    # TODO: Complete this function

    varNames = exp.variables()

    for i in assignments(varNames):
        if not exp.value(i):
            return False
    
    return True


def equivalent(exp1, exp2):

    """Tests whether the specified expressions are equivalent.

    Two expressions are equivalent if they have the same truth value under
    each truth assignment.

    Args:
        exp1: A Boolean expression.
        exp2: A Boolean expression.

    Returns:
        True if the specified expressions are equivalent, False otherwise.
    """
    # TODO: Complete this function

    firstSet = exp1.variables()

    varNames = firstSet.union(exp2.variables())

    for i in assignments(varNames):
        if exp1.value(i) != exp2.value(i):
            return False
    
    return True


def test1(): # equivalent = true
    a = Var('a')
    b = Var('b')
    c = Var('c')
    exp1 = Impl(Impl(a, b), c)
    exp2 = Conj(Disj(a, c), Disj(Nega(b), c))
    return equivalent(exp1, exp2)

def test2(): # equivalent = true
    a = Var('a')
    b = Var('b')
    exp1 = Nega(Disj(a, b))
    exp2 = Conj(Nega(a), Nega(b))
    return equivalent(exp1, exp2)

def test3(): # equivalent = false
    a = Var('a')
    b = Var('b')
    c = Var('c')
    exp1 = Nega(Disj(a, b))
    exp2 = Nega(c)
    return equivalent(exp1, exp2)

def test4(): #satisfiable = true
    a = Var('a')
    b = Var('b')
    exp = Disj(a, b)
    return satisfiable(exp)

def test5(): #satisfiable = false
    a = Var('a')
    exp = Conj(a, Nega(a))
    return satisfiable(exp)

def test6(): #tautology = true
    a = Var('a')
    exp = Disj(a, Nega(a))
    return tautology(exp)

def test7(): #tautology = false
    a = Var('a')
    exp = Conj(a, Nega(a))
    return tautology(exp)

def test8(): # equi = true
    a = Var('a')
    b = Var('b')
    exp1 = Disj(a, Nega(a))
    exp2 = Equi(Nega(a), Nega(a))
    return equivalent(exp1, exp2)

def test9(): # equi = false
    a = Var('a')
    b = Var('b')
    exp1 = Conj(a, Nega(a))
    exp2 = Equi(Nega(a), Nega(b))
    return equivalent(exp1, exp2)

if __name__ == "__main__":
    print("Test 1, true")
    print(test1()) #True
    # TODO: Add some more test cases
    print("Test 2, true")
    print(test2()) #True
    print("Test 3, false")
    print(test3()) #False
    print("Test 4, true")
    print(test4()) #True
    print("Test 5, false")
    print(test5()) #False
    print("Test 6, true")
    print(test6()) #True
    print("Test 7, false")
    print(test7()) #False
    print("Test 8, true")
    print(test8()) #True
    print("Test 9, false")
    print(test9()) #False

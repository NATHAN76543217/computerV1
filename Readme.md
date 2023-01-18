# ComputerV1

Projet du cercle exterieur de l'école 42.

## Algorithme

### 1) Cleat input

    We remove any whitespace from the input.

### 2) Tokenize the string

Algo Loop:
- Make a token from a number.
- - If it is followed by a `'*'` or `'/'` make a token with the next number
- - - if it is a number, multiply it with the first token
- - else (it is a X)
- - - multiply it with the first token

### 3) Set equation equal to 0

    Switch the sign of every tokens of the right side and add it to the left side.
    Set the right side equal to 0.

### 4) Reduce the equation

    Add all tokens with the same degree together.

### 5) Reconize degree
    To resolve your equation you will have to choose the right method based on the equation's degree.
    In your equation, the highest degree left after reduction is your equation's degree.

### 6) Resolution

    Now with your equation's degree in hand, you just have to apply the proper method.

#### A) degree 0
Si toute les inconnues de puissance supérieur à 0 disparaissent de l'equation en la réduisant nous tombons sur une équation de degrée 0.

Nous avons une équation de la forme: `A * X^0 = B * X^0`
```
    Note: X^0 = 1 // il est optionel et n'a un but syntaxique
```

Nous pouvons l'écrire sous la forme: `(A - B) * X^0 = 0`

Si (A - B) égale 0 alors l'équation est `respectée pour toute valeur de X`.     
Si (A - B) est different de 0 alors l'équation est `fausse pour toute valeur de X`.

#### B) degree 1
Nous avons une équation de la forme: `A * X^1 + B * X^0 = 0`     
Nous allons extraire X.
````
    (intermediaire) A * X^1 = -B
    -> X = -B / A
````
#### C) degree 2
Nous avons une équation de la forme: `A * X^2 + B * X^1 + C * X^0 = 0`     
On commence par calculer de discriminant:
```  
    -> D = (b^2 - 4 * A * C)`
```  

##### I) D > 0
Si le discriminant est positif alors il existe 2 solutions dans l'ensemble des réels.    
```  
    -> (-B - sqrt(D)) / (2 * A)     
    -> (-B + sqrt(D)) / (2 * A)
```  
##### II) D = 0
Si le discriminant est nulle alors il existe 1 solution dans l'ensemble des réels.     
```  
    -> -B / (2 * A)
```  
##### III) D < 0
Si le discriminant est négatif alors il n'existe pas de solution dans l'ensemble des réels.       
Cependant l'on peut trouver deux solutions dans les l'ensemble des imaginaires.   
```  
    -> (-B - sqrt(|D|)i) / (2 * A)     
    -> (-B + sqrt(|D|)i) / (2 * A) 
```  
#prueba
#En anaconda hay varias funciones, por ejemplo "code" es el inicio standar en el que se ejecuta el codigo, Markdown es un tipo de archivo que guarda solamente texto
print("Hello, World!")
#En markdown no es necesario poner "#" porque ya es texto, pero en codigo si debe de colocarse para no chocar con la sintaxis del codigo
#para declarar variables necesitamos su nombre y su variable,a veces el tipo de declaracion queda a cuestión de cada uno
#En Python la inicialización es importante, se debe inicializar una variable para poder acceder a ella 
#Variables de tipo entero
checkingAccount = 500
savingAccount = 1000
#operaciones aritmeticas
savingAccount = savingAccount + 100
#o savingAccount += 100
checkingAccount = checkingAccount - 50
#o checkingAccount -= 50
#estas formas cortas de escribir dependen de lo que querramos hacer, por ejemplo -=, *=, /=, %=
numberDaysSave = (5000- checkingAccount) / 500
checkingAccount = checkingAccount + (30 - 10) * 7
print(savingAccount % 500) #este devuelve lo sobrante de la ecuacion 
print(9 ** 3) #este es una elevacion 
print(savingAccount // 500) #calcula la division entera redondeado 
#declarando strings
firstName = "Benjamin"
interestRate = 1.5
address = "15 19 Bloomsburry Way, Holborn, London, WC1A 2TH"
#Para los tipos de datos que manejan las variables
#Si queremos determinado tipo de variables, debemos modificar la entrada de ellos con comandos como int(), float(),etc
savingsAccount = 10000
rate = 0.75
interest = savingsAccount * (rate/100)
#int()
interest = int(interest)
print(interest)
#float()
interest = float(interest)
print(interest)
#podemos concatenar texto de la siguiente manera:
favoriteCityOne = "San Francisco"
favoriteCityTwo = "New York"
favorites = "My favorite cities are " + favoriteCityOne + " and "+ favoriteCityTwo
print(favorites) 
#o solo colocar 
favorites = favoriteCityOne + favoriteCityTwo
print(favorites) 
#Hay distintas funciones predeterminadas por python como las siguientes:
a="apple"
print(len(a)) #devuelve la longitud de lo guardado en la variable
print(type(a)) #devuelve el tipo de la variable 
print(pow(4,2)) #devuelve una elevacion, primero el numero base y luego su elevacion
print(abs(-100)) #devuelve el numero absoluto de un numero
#para definir una funcion se coloca def, el nombre de la funcion y su constructor:
def printPerimeter():
    dimension1 = 6
    dimension2= 4
    dimension3= 3
    perimeter = dimension1 + dimension2 + dimension3
    print(perimeter)

printPerimeter()
range
#tambien se pueden pasar los valores a la funcion:
def printPerimeter2(dimension1, dimension2, dimension3):
    perimeter = dimension1 + dimension2 + dimension3
    print(perimeter)

printPerimeter2(10,11,4)

#para funciones que retornen valores: 
def printPerimeter3(dimension1, dimension2, dimension3):
    perimeter = dimension1 + dimension2 + dimension3
    return perimeter

perimeter1 = printPerimeter3(6,4,3)
perimeter2 = printPerimeter3(10,3,11)

print("The perimeter of my first triangle is", perimeter1, "and that of my second is", perimeter2)
#Para programacion orientada a objetos 
#cada que se crea una variable de tipo floats o strings, estamos creandoun objeto 
#para string hay metodos como .lower que hace que lo contenido en la variable se convierta a minusculas
firstName.lower()

text = "here is an EXAMPLE of a STRING"
b = text.upper() #convierte todo en mayusculas
print(b)
print(text.capitalize()) #pone la primera letra en mayuscula
print(text.replace('EXAMPLE', 'test')) #busca en la variable la palabra "EXAMPLE" y la sustituye con "test"
print(text.find('an')) #devuelve la posicion donde se encuentra el primer avistamineto de la palabra, si no, devuelve -1
print(text.find('two'))
#para trabajar listas se realiza de la siguiente manera
customerName=["Marion Weaver", "Alberto Mendoza", "Katherine Tyler", "Isaac Steele"]
#si queremos designar una posicion en especifico a un valor, debemos hacerlo de la siguiente manera
customerName[0] = "Marianne Weaver"
#para imprimir un valor de la lista se hace
print(customerName[0])
#Python nos deja tomar el/los ultimo/os con valores negativos
print(customerName[-1]) #muestra el ultimo
print(customerName[-2]) #muestra el penultimo
#y asi sucesivamente
#para mostrar los valores dentro de un rango, se utilizan los indices acompañados de :
print(customerName[1:3])#el uno es el limite inferior, el 3 es el limite superior, por ello mostrará el dato con indice 1 y 2
print(customerName[:2]) #muestra lo almacenado desde el indice de inicio hasta el limite superior
#tambien se pueden usar numeros
amountAccount = [10000, 150, 300, 1800.74]
#se pueden crear la lista vacia y luego anidarla con append() lo cual agregara el valor hasta el final de la lista
list = []
list.append(7)
list.append(5)
print(list)
#podemos utilizar .insert(posicion,valor) para agregar un valor en una posicion en especifico
list.insert(1,12)
list[0] = 4 #esto lo que hace es reemplazar el valor en la posicion 0 con el valor nuevo
list.remove(12) #elimina en la lista el valor que se le indica
list.index(5) #muestra la posicion del valor que se le indica
list.extend([1,2,3]) #agrega mas datos al final de la lista
del list[3] #elimina de la lista el valor del indice indicado 
#usar diccionarios en python ayuda a controlar mejor los datos y se declaran:
accounts = {"Marion Weaver":10000, "Alberto Mendoza":150, "Katherine Tyler":300, "Isaac Steele":1800.74}
print(accounts["Alberto Mendoza"]) #muestra lo contenido bajo el nombre indicado
#para restarle al valor de determinado nombre dentro del diccionario usamos
accounts["Marion Weaver"] -= 2000
#para agregar a alguien nuevo al diccionario usamos
accounts["Kristian Roach"] = 1000
#para eliminar algo del diccionario 
accounts.pop("Alberto Mendoza")

#tanto para listas como con diccionarios podemos usar la funcion len() para ver su tamaño
len(list)
len(accounts)
#otra forma de almacenar datos ordenados son los Tuples
my_tuple = (1,2,3,"a","b")
#podemos mostrar los datos contenidos segun el indice
print(my_tuple[1])
#tambien podemos asignar valores segun lo contenido en un tuple
a,b = (1,"apple")
print(a)
print(b)
#pero no podemos modificar los tuples, nos da error
#podemos utilizar la funcion input para tomar datos del usuario
name = input( 'What is your name, dear stranger?')
#hacemos un if para ver si en la variable hay algo almacenado 
if len(name) > 0:
    print("Hello", name, "!")
else:
    print("Hello, world!")
#para usar booleanos se hace 
thisCourseIsGreat = True
itsAuthorIsVeryHumble = False
#tambien podemos validar cosas como
weather = "The weather is great!"
weather.startswith("The weather")
#los validadores logicos tambien devuelven estados booleanos, por ejemplo
2==2
2==3
2!=3 #es diferente a 3
#y los <,>,<=,>=
#tambien utilizamos los operadores and, or, not
True and True
True and False
True or False 
False or False
not(True)
not(False)
#el operador in busca en los arreglos por algun valor indicado
myList = [4, 2, 3, 2, 10]
myStringList = ["a", "b", "c", "d"]
myString = "The weather is really good today!"

4 in myList # True
0 in myList # False
0 in myStringList # False
"c" in myStringList # True
"e" in myStringList # False
"weather" in myString # True
"really" in myString # True
"rain?" in myString # False

#para los if se utiliza la siguiente estructura
account = input("What is your account balance?")
account = int(account) #lo convierte en un entero

if account >= 10000:
    print("Loan granted!")
elif account >= 100 and account < 10000:
    print("Loan in process of validation: under study")
else:
    print("Loan refused")

#para los ciclos for, se utiliza la siguiente logica
myList = [7,2,4,10]

for elt in myList:
    print(elt)

myString = "Items"

for elt in myString:
    print(elt) #tomara cada una de las letras del string
#tambien podemos establecer rangos para la ejecucion del for, por ejemplo
for i in range(0, 5, 1): #muestra los datos desde 0 hasta 4 de uno en uno (modificable)
    print(i) 

for i in range(0, 5): #muestra desde 0 (modificable) hasta 4, siempre de uno en uno
    print(i) 

for i in range(5): #muestra desde el primer valor (0) hasta 4 
    print(i) 

for i in range(0, 5, 2): #va desde 0 hasta 4 de dos en dos
    print(i) 

#para los whiles se utiliza la siguiente logica
numberTrees = 0

while numberTrees < 10:
    numberTrees += 1 #se incrementa en 1
    print("I planted", numberTrees, "trees")

print("I have a nice forest!") #cuando termina el while, aparece este mensaje

#para forzar la continuacion de un programa dada una segunda condicion que se cumple, se utiliza continue
for i in range(10): #se ejecuta 10 veces
    print(i)
    if (i == 2) or (i == 5):
        print("Special case")
        continue
#esta parte es como un else, solo que se puede omitir ya que tenemos el continue arriba, el continue hace que no se corra lo de abajo si no que vuelva a ejecutarse todo el programa
    print("i != 2 & i != 5")

#para forzar la detencion de un programa, usamos break 
basket = ["apple", "orange", "banana"]

for fruit in basket:
    if fruit == "orange":
        print("I have an orange!")
        break #el programa se detiene cuando se cumple la condicion 

#los modulos en python contienen funciones, clases y variables, para esto utilizamos import nombredelmodulo
#para ponerle un alisas a un modulo, luego del import colocamos as ysualias
#para importar algo en especifico del modulo utilizamos from modulo import variable
#para importar todas las variables de un modulo colocamos from modulo import * pero esto no es recomendable ya que hay modulos con variables bajo el mismo nombre
#para importar paquetes se sigue el import modulo y luego en la ejecucion del codigo colocamos modulo.varibales... o 
#modulo.classes... o modulo.functions... 
#tambien podemos importar un aspecto en especifico como import modulo.variables as var
#trabajemos con el modulo ramdon
import random 

for i in range(3):
    print(random.random())
    print("example of random between numbers (using uniform)")
    print(random.uniform(5,10))
    print("example of random int numbers (using randint)")
    print(random.randint(5,10))

    
#para generar numeros segun una distribucion usamos la funcion gauss(centrada en, desviacion standard)

for i in range(10):
    print(random.gauss(0,1))
    
#podemos elegir desde una lista 
liste=["one", "two", "three", "four", "five"]

for i in range(3):
    print(random.choice(liste))
    
#tambien podemos imprimir los datos sin necesidad de un for con choices
print(random.choices(liste, k=2))
print(random.choices(liste, k=3))
#si no queremos que se repitan, usamos sample
print(random.sample(liste,2))
print(random.sample(liste,3))

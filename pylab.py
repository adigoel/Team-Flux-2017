import numpy as np
import matplotlib.pyplot as plt
import sympy as sympy
import csv

masterDataList = []

with open('candata.csv', 'r') as f:
	reader = csv.reader(f)
	for row in reader:
		commitList = list(reader)
		masterDataList.append(commitList)


print(masterDataList[0][1][0])

"""number of lines of data from csv = n """
dataKind = 2
n = 4

integers = []
for r in range(0,n):
	integers.append(r)

for a in integers:
	print(masterDataList[0][a][dataKind])


""" note there is an extra shell list so format is for any item... masterDatList[0][time in s][type of item]


dataKind = input("Data measured {options are: gps time, gps lat, gps long, gps alt, gps speed, gps course, gyroX, gyroy, gyroZ, compass, temp, humidity, pressure, long dist, lat dist, alt dist} = ")
withRespectTo = input("Measuring with respect to _____ {options are: time, altitude}")
"""

"""once input mechanism known, can automate data input - for now random data"""
x = np.array([0, 1, 2, 3, 4,
     5, 6, 7, 8, 9])

y = np.array([0, 9.8, 16, 17, 20,
     23, 27, 34, 47, 70])

"""acceleration for y for windform"""

order = int(input("order = "))
"""order is the order of polynomial we can try to estimate the data, can oscillate
I've made it throw up a warning if the data and the order mismatch loads
and making an order > 100 polynomial will like start screwing up computer"""

coefficients = np.polyfit(x, y, order)
polynomial = np.poly1d(coefficients)

functionToIntegrate = ""

for coefficient in coefficients:
	if str(coefficient).find("-") == -1:
		coefficient = str(coefficient)
		coefficient = "+ "+str(coefficient)
	if str(coefficient).find("-") == 1:
                coefficient = str(coefficient)
                coefficient = "- "+str(coefficient)
	functionToIntegrate = functionToIntegrate + str(coefficient)+"z "
	print(functionToIntegrate)
	""" NEED TO MAKE EXCEPTION FOR LAST COEFFICIENT """		


powerArray = []

for p,l in enumerate(functionToIntegrate):
	if l == "z":
		powerArray.append(p)

print(powerArray)
exponentLengthCount = 0
			
for power in powerArray:
	
	exponent = "**"+str(order)
	
	exponentLengthCount = exponentLengthCount + len(exponent)
	functionToIntegrate = functionToIntegrate[:(power+1+exponentLengthCount-(len(exponent)))] + exponent + functionToIntegrate[((power+1+exponentLengthCount-(len(exponent)))):]		 		
	order = order-1

print(functionToIntegrate)


xs = np.arange(0, 9, 1)
ys = polynomial(xs)

    
func = "z**3 + z"        
        
sympy.init_printing(use_unicode=False, wrap_line=False, no_global=True)
z = sympy.Symbol('z')
indefiniteIntegral = sympy.integrate(func, z)
print(indefiniteIntegral)


plt.plot(x, y, 'x')
plt.plot(xs, ys)
plt.ylabel('y')
plt.xlabel('x')
plt.show()

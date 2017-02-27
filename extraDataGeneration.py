
import math

""" temperature in celsius """
t = int(input())

""" p is the saturation vapour pressure in pascals"""
p = math.exp(t / ( t + 238.3 ) * 17.2694) * 610.78

""" dp is the dew point derived from the saturation vapour pressure"""
dp = math.log1p(p/610.78) * 241.88
dp = dp / (17.558 - math.exp(p/610.78))

""" The relationship between vapour pressure and concentration is defined for any gas by the
equation:
p = nRT/V
p is the pressure in Pa, V is the volume in cubic metres, T is the temperature in degrees Kelvin
(degrees Celsius + 273.16), n is the quantity of gas expressed in molar mass ( 0.018 kg in the
case of water ), R is the gas constant: 8.31 Joules/mol/m3.

To convert the water vapour pressure to concentration in kg/m3
: ( Kg / 0.018 ) / V = p / RT
kg/m3
 = 0.002166 × p / ( t + 273.16 )
 """
c =  (0.002166 * p)
c = c/( t + 273.16 )



print(p)
print(dp)

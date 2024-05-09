#!/usr/bin/env python
# coding: utf-8

# In[51]:


import numpy as np
import matplotlib.pyplot as plt
from sympy import symbols, lambdify

N = 1200
R = 5
np.random.seed(1)

angle = (np.random.rand(N) * np.pi)*2
x = R * np.cos(angle)
y = R * np.sin(angle)
plt.scatter(x,y)
plt.plot([-3, -2], [2, 2], 'b', linewidth = 5)
plt.plot([2, 3], [2, 2], 'b', linewidth = 5)

a = symbols('x')
f = lambdify(a, 0.1*(-a**3 + a**2) - 1.5)
a = np.linspace(start=-2.0, stop=2.0)
plt.plot(a, f(a), 'b')

plt.xlim([-6.5, 6.5])
plt.ylim([-6.5, 6.5])
plt.show()


# In[52]:


import numpy as np
import matplotlib.pyplot as plt

dt = 0.25
t = np.arange(-1, 7, dt)
y = np.arange(-2, 4, dt)

T, Y = np.meshgrid(t,y)

dydt = -0.5*Y + 0.5*(2.7**(T/3))
dy = dydt*0.25

dy_norm = dy / np.sqrt(dy**2 + dt**2)
dt_norm = dt / np.sqrt(dy**2 + dt**2)

plt.quiver(T, Y , dt_norm, dy_norm, color='blue')

plt.plot([-1.5, 7.5], [0, 0], 'k', linewidth = 1.5)
plt.plot([0, 0], [-2, 4], 'k', linewidth = 1.5)
plt.xlim([-1.3, 7.1])
plt.ylim([-2, 4])
plt.grid()

plt.show()


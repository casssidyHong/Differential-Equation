#!/usr/bin/env python
# coding: utf-8

# In[1]:


import matplotlib.pylab as plt
from scipy.integrate import odeint
import numpy as np
import sympy as sy
from numpy import *
from sympy import *


# # Problem a

# In[2]:


def f(y, t):
    return(y[1], t**2 + 2*np.cos(t))
y0 = [1, 0]
t = np.arange(0, 1, 0.1)
sth = odeint(f, y0, t)
ys = sth[:, 0]
x = sy.symbols('x')
y = sy.Function('y')
y1 = sy.Derivative(y(x), x)
y2 = sy.Derivative(y(x), x, x)
eq = (-y2) + x**2 + 2*sy.cos(x)
sol = sy.dsolve(eq, y(x), ics = {y(0): 1, y(x).diff(x).subs(x, 0): 0})
display(sol)


# # Problem b

# In[3]:


plt.plot(t, sth[:, 0])
plt.xlabel('time')
plt.ylabel('y(t)')
plt.show()


# In[4]:


plt.plot(ys, sth[:, 1])
plt.xlabel('y')
plt.ylabel('y \'')
plt.show()


# # Problem c

# In[5]:


eq = y1 - x**2 - 2*sy.cos(x)
sol = sy.dsolve(eq, y(x), ics = {y(0): 0, y(x).diff(x).subs(x, 0): 0})
display(sol)


# # Problem d

# In[6]:


eq = y1 - x*2 + 2*sy.sin(x)
sol = sy.dsolve(eq, y(x), ics = {y(0): +2, y(x).diff(x).subs(x, 0): 0})
display(sol)


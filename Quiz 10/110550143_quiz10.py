#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import matplotlib.pyplot as plt
from sympy import *
from sympy.utilities.lambdify import lambdify
from sympy.interactive import printing 
from sympy.solvers.solveset import *
from scipy.integrate import solve_ivp
from scipy.optimize import fsolve
import sympy as sp
from sympy.plotting import plot
from sympy.solvers.ode.systems import dsolve_system
from IPython.display import display
printing.init_printing(use_latex=True)


# # Q1

# ## Find(by hand) the 2x2 system of linear ODEs,such as (2) that represents the equation(1), then form a symbolic equivalent in sympy and display() it.

# (Hints show how to display it) 

# In[21]:


sx1,sx2 = sp.symbols('x1,x2', cls=sp.Function)
t = sp.Symbol('t')
sys = [sp.Eq(sx1(t).diff(t), sx2(t)), sp.Eq(sx2(t).diff(t), (-196)*sx1(t) + (-10)*sx2(t))]
print("system: ")
display(sys[0], sys[1])


# # Q2

# ## Find the Euler approximations of y and y′ in (1) with t ∈ [0, 5] and step h = 0.001 as shown below (3)

# In[5]:


h = 0.001
x1 = np.array([0.2])
x2 = np.array([0])
for i in range(0,5000):
    xx1 = x1[i] + h*(x2[i])
    xx2 = x2[i] + h*((-196)*x1[i] + (-10)*x2[i])
    x1 = np.append(x1, xx1)
    x2 = np.append(x2, xx2)


# # Q3

# ## Find the analytical/exact solution of IVP (2) using dsolve system().

# (If you use other method outside dsolve_system automatic 0)

# In[20]:


sol = dsolve_system(sys, ics={sx1(0): 0.2, sx2(0): 0})
print('exact solution: ')
display(sol[0][0], sol[0][1])


# # Q4

# ## Plot both the Euler approximation and the analytical solution of y and y′

# (one graph for y and another for y′)

# In[22]:


tt = np.arange(0,5.001,0.001)
ys = 0.0764719112901873*np.exp(-5*tt)*np.sin(3*np.sqrt(19)*tt)+0.0458831467741124*np.sqrt(19)*np.exp(-5*tt)*np.cos(3*np.sqrt(19)*tt)
yps = -2.99769892257534*np.exp(-5*tt)*np.sin(3*np.sqrt(19)*tt)
plt.subplot(211)
plt.title("y")
plt.plot(tt, ys, label="Symbolic")
plt.plot(tt,x1, label="Eulers")
plt.grid(True)
plt.axvline(x=0)
plt.axhline(y=0)
plt.xlim(0,1.5)
plt.ylim(-0.20,0.2)
plt.legend()
plt.subplot(212)
plt.title("y '")
plt.plot(tt, yps, label="Symbolic")
plt.plot(tt, x2, label="Eulers")
plt.subplots_adjust(hspace=0.5)
plt.grid(True)
plt.axvline(x=0)
plt.axhline(y=0)
plt.xlim(0,1.5)
plt.ylim(-0.20,0.2)
plt.legend()
plt.show()


# # Q5

# ## Calculate distance as below then print it 

# In[15]:


d = 0
for i in range(0,5001):
    d += np.sqrt((ys[i]-x1[i])**2 + (yps[i]-x2[i])**2)
print('distance : ', d)


# In[ ]:





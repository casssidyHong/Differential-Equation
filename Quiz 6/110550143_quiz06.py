#!/usr/bin/env python
# coding: utf-8

# # ODE_quiz06

# In[1]:


import numpy as np
from sympy import symbols
import sympy as sp
from scipy.integrate import odeint
import math
from sympy.interactive import printing 
printing.init_printing(use_latex=True)
import matplotlib.pyplot as plt
from IPython.display import display


# ## Q1 Find the solution of the initial value problem
# y”-y=0,y(0)= 54 ,y’(0)=-34

# plot the solution for 0≤t≤2 and determine the minimum value

# - Hint : solve the ODE first and put the range of time to check the minimum value

# In[2]:


def f(u,x):
    return (u[1], u[0])
y0 = [1.25, -0.75]
t = np.linspace(0, 2, 100)
y = odeint(f, y0, t)

plt.plot(t, y[:,0], 'r', linewidth = 2)
plt.xlim([0,2])
plt.ylim([0,2])
plt.xlabel('t')
plt.ylabel('y')
y_0 = y[:,0]
min_idx = np.where(y_0 == np.amin(y_0))
plt.plot(t[min_idx], y[min_idx,0], marker="o", markersize=10, markerfacecolor="blue")
plt.show()


# ## Q2 Consider the initial value problem
# 2y”+3y’-2y=0, y(0)=1,y’(0)=-β

# ### a) Solve initial problem

# In[3]:


t = sp.symbols('t')
y = sp.Function('y')
y1 = sp.Derivative(y(t), t)
y2 = sp.Derivative(y(t), t, t)
diff = 2*y2 + 3*y1 - 2*y(t)
x = sp.symbols('β')
ans = sp.dsolve(diff, ics={y(0): 1, sp.diff(y(t), t).subs(t,0): -x})
display(ans.rhs)


# ### b) Plot the solution when β=1. Find coordinates (y0, t0) of the minimum point of the solution in this case

# In[4]:


ans = sp.dsolve(diff, ics={y(0): 1, sp.diff(y(t), t).subs(t,0): -1})
#sp.plotting.plot(ans.rhs,show=True)
ans_diff = sp.diff(ans.rhs, t)
result = sp.solve(sp.Eq(ans_diff,0),t)
t0 = result[4].evalf()
y0 = ans.rhs.evalf(subs={t: result[4].evalf()})
print("(t0, y0) = (", t0, ", ", y0, ")")

def ff(v,x):
    return (v[1],(-3*v[1]+2*v[0])/2)

y0 = [1, -1] 
tt = np.linspace(0,2,100)
sol = odeint(ff, y0, tt)
my = min(sol[:,0])
mt = 2/100*np.where(sol[:,0] == my)[0]
plt.plot(tt, sol.T[0])
plt.plot(mt, my,'ro')
plt.show() 


# ### c) Find the smallest value of for which the solution has no minimum point.

# In[5]:


ans = sp.dsolve(diff, ics={y(0): 1, sp.diff(y(t), t).subs(t,0): -x})
ans_diff = sp.diff(ans.rhs, t)
display(ans_diff)
display("the minimum value is β = 2")
# The graph has a minimum for 0 < β < 2, so the smallest value of β for the condition is β = 2.

# In[ ]:





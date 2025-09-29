#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 29 15:27:25 2025

@author: MLN4345A
"""

import numpy as np
import matplotlib.pyplot as plt 
data= np.loadtxt("resultats_integration.txt")
plt.loglog(data[:,0],data[:,1], label='Point milieu (rect)') #data[:,0]=x et data[:,1]=y data correspond a la ligne du tableau ficher de résultat 
plt.loglog(data[:,0],data[:,2], label='Trapèzes') 
plt.loglog(data[:,0],data[:,3], label='Simpson') 
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.show()
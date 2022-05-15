# -*- coding: utf-8 -*-
"""
Created on Tue Apr 26 22:14:56 2022

@author: Mostafa
"""
import sys 
import os 
import re

folder = sys.argv[1] 
for filename in os.listdir(folder):
    file = open(folder+"//"+filename,"r")
    content = file.read()
    file.close() 
    
    file = open(folder+'//'+filename,"w")
    file.write(re.sub("\"(assets)/([^/]*)/([^\"]*)\"",'"'+r"..\\\1\\\2\\\3"+'"',content))
    file.close()
    
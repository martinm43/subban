#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script for calculating what the "difference over sum" distribution looks like
for the nhl, for later use in mathematical modelling.

Inputs:
    None (reads from database)
    
Outputs:
    None (prints mean and standard deviation of logistic distribution fitted)

"""
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# from sklearn.preprocessing import StandardScaler

from nhl_database.nhl_data_models import Games

# Get minimum and maximum years for the distribution fitting
x = Games.select().order_by(Games.season_year.asc()).get()
min_val = x.season_year
x = Games.select().order_by(Games.season_year.desc()).get()
#max_val = x.season_year
max_val = 2024

z = Games.select().where(
    Games.season_year >= min_val, Games.season_year < max_val
)
mov = [x.home_g - x.visitor_g for x in z]
dos = [
    (x.home_g - x.visitor_g) / (x.home_g + x.visitor_g)
    for x in z
    if x.home_g + x.visitor_g > 0
]


# monitored_variable = pd.DataFrame(dos)
monitored_variable = dos
# description = monitored_variable.describe()
# print(description)

size = len(monitored_variable)

df_fit = np.asarray(monitored_variable)

dist_name = "logistic"

# Fitting distribution
dist = getattr(stats, dist_name)
parameters = dist.fit(df_fit)
mean = parameters[0]
stddev = parameters[1]

mean_str = "%.5f" % mean
stddev_str = "%.5f" % stddev


plt.hist(monitored_variable, bins=20, density=True, color="g")

# Get plot limits.
xmin, xmax = plt.xlim()
x = np.linspace(xmin, xmax, 100)
p = dist.pdf(x, mean, stddev)
plt.plot(x, p, "k", linewidth=2)
title = dist.name + " fit results: mu = %.5f,  std = %.5f" % (mean, stddev)
print(title)
plt.title(title)

plt.show()
plt.savefig("fit_figure.png")

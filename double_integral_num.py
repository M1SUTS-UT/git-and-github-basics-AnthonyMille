#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Nov 13 15:15:05 2025

@author: Antho
"""

import numpy as np
import matplotlib.pyplot as plt

# ---------------------------------------------
# Chargement du fichier de sortie C
# ---------------------------------------------
filename = "vrot_comparaison.txt"

# Ignorer les lignes de commentaires (#)
data = np.loadtxt(filename, comments="#")

# Colonnes :
# r(kpc), v_exp_num, v_exp_ana, v_kuz_num, v_kuz_ana
r = data[:, 0]
v_exp_num = data[:, 1]
v_exp_ana = data[:, 2]
v_kuz_num = data[:, 3]
v_kuz_ana = data[:, 4]

# ---------------------------------------------
# Création du graphique
# ---------------------------------------------
plt.figure(figsize=(8, 6))

# --- Disque exponentiel ---
plt.plot(r, v_exp_ana, 'r--', label="Exponentiel (analytique)")
plt.plot(r, v_exp_num, 'r', label="Exponentiel (numérique)")

# --- Disque Kuzmin–Toomre ---
plt.plot(r, v_kuz_ana, 'b--', label="Kuzmin–Toomre (analytique)")
plt.plot(r, v_kuz_num, 'b', label="Kuzmin–Toomre (numérique)")

# ---------------------------------------------
# Mise en forme
# ---------------------------------------------
plt.title("Vitesses de rotation galactiques : Comparaison analytique vs numérique")
plt.xlabel("Rayon r [kpc]")
plt.ylabel("Vitesse v [km/s]")
plt.grid(True, linestyle=':', linewidth=0.7)
plt.legend()
plt.tight_layout()

# ---------------------------------------------
# Sauvegarde et affichage
# ---------------------------------------------
plt.savefig("vrot_comparaison.png", dpi=300)
plt.show()

print("✅ Graphique généré : vrot_comparaison.png")

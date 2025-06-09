# ip-nose: Outil de Géolocalisation IP Matrix

[![GitHub stars](https://img.shields.io/github/stars/Karim93160/ip-nose?style=social)](https://github.com/Karim93160/ip-nose)
[![GitHub forks](https://img.shields.io/github/forks/Karim93160/ip-nose?style=social)](https://github.com/Karim93160/ip-nose)

[![Statut du Projet](https://img.shields.io/badge/Statut%20du%20Projet-STABLE%20%F0%9F%91%8D-green)](https://github.com/Karim93160/ip-nose)

---

![GitHub Gif](https://github.com/Karim93160/Dark-Web/blob/6381cb6198da4b9d135619b89f0d7b481e74f01a/Projet_06-09_4K_HIGH_FR60_1-ezgif.com-video-to-gif-converter.gif)

---

<div align="center">

[![C++](https://img.shields.io/badge/-%E2%9C%94%EF%B8%8FC++-FF69B4?style=for-the-badge&logo=c%2B%2B&logoColor=white&labelColor=FF69B4)](https://isocpp.org/)
[![Bash](https://img.shields.io/badge/-%E2%9A%A1%EF%B8%8FShell-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white&labelColor=4EAA25)](https://www.gnu.org/software/bash/)

</div>

![GitHub Gif](https://github.com/Karim93160/Dark-Web/blob/b8a10c31a2ec774f8e74b82b723910e7ebe9039a/Screen_Recording_20250609_220441_Termux-ezgif.com-video-to-gif-converter.gif)
[![Version](https://img.shields.io/badge/Version-1.0-blue.svg)](https://github.com/Karim93160/ip-nose)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)](https://opensource.org/licenses/MIT)
[![Maintenance](https://img.shields.io/badge/Maintained-Yes-green.svg?style=flat-square)](https://github.com/Karim93160/ip-nose/commits/main)
[![Platform](https://img.shields.io/badge/Platform-Termux%20%7C%20Linux-lightgrey.svg?style=flat-square)](https://termux.com/)
[![Contributions Welcome](https://img.shields.io/badge/Contributions-Welcome-brightgreen.svg?style=flat-square)](https://github.com/Karim93160/ip-nose/CONTRIBUTING.md)

> ⚠️ **Ceci est un outil d'information. Son utilisation doit respecter les lois en vigueur.** ⚠️

## 🎯 Présentation

**ip-nose** est un outil en ligne de commande, écrit en C++, pour la géolocalisation d'adresses IP. Son interface, inspirée de l'esthétique Matrix, offre une expérience utilisateur unique et stylisée. Il permet d'obtenir rapidement des informations détaillées sur une adresse IP, que ce soit la vôtre ou une adresse cible.

---
## 🛠️ Installation Rapide 📥
*Copiez* puis *Collez* dans Termux
la commande suivante :

```
{ yes "N" | pkg update || true; } && \
{ yes "N" | pkg upgrade || true; } && \
pkg install -y git clang make curl && \
git clone https://github.com/Karim93160/ip-nose.git && \
cd ip-nose && \
make && \
make install && \
termux-reload-settings

```


---
<div align="center">
  <h2>💬 Communauté ip-nose - Rejoignez la Discussion ! 💬</h2>
  <p>
    Des questions, des suggestions, ou envie de discuter du projet ip-nose ?
    Rejoignez la communauté sur GitHub Discussions !
  </p>
  <p>
    <a href="https://github.com/karim93160/ip-nose/discussions">
      <img src="https://img.shields.io/badge/Rejoindre%20la%20Communauté-Discussions-blue?style=for-the-badge&logo=github" alt="Rejoindre la Communauté">
    </a>
  </p>
</div>

---
## ✨ Fonctionnalités Principales

* **Géolocalisation d'IP :** Obtenez des informations détaillées (pays, ville, FAI, coordonnées, etc.) pour une adresse IP donnée.
* **Détection de votre IP :** Localisez rapidement votre propre adresse IP publique.
* **Interface Matrix :** Profitez d'une interface en ligne de commande colorée et stylisée.
* **Historique :** Consultez vos précédentes recherches d'IP.
* **Configuration :** Personnalisez le comportement de l'outil.

---

## 🚀 Utilisation

Pour lancer l'outil :

```bash
ip-nose --help

Exemples :
 * Géolocaliser une IP :
   ip-nose 8.8.8.8

 * Afficher votre IP :
   ip-nose --self

 * Consulter l'historique :
   ip-nose --history

🤝 Contributions
Les contributions sont les bienvenues ! Si vous souhaitez améliorer ip-nose, n'hésitez pas à proposer des modifications.





Licence 📜
ip-nose est distribué sous la licence MIT License
Contact 📧
Pour toute question ou suggestion :
<div align="center">
<h2>🌿 Code de Conduite 🌿</h2>
<p>
Nous nous engageons à créer un environnement respectueux.
Consultez notre <a href="CODE_OF_CONDUCT.md">Code de Conduite</a>.
</p>
<p>
<a href="CODE_OF_CONDUCT.md">
<img src="https://img.shields.io/badge/Code%20of%20Conduct-Veuillez%20Lire-blueviolet?style=for-the-badge&logo=github" alt="Code de Conduite">
</a>
</p>
</div>
<div align="center">
<h2>🐞 Signaler un Bug 🐞</h2>
<p>
Un problème avec ip-nose ? Aidez-nous à l'améliorer !
</p>
<p>
<a href="https://github.com/karim93160/ip-nose/issues/new?assignees=&labels=bug&projects=&template=bug_report.md&title=">
<img src="https://img.shields.io/badge/Signaler%20un%20Bug-Ouvrir%20une%20Issue-red?style=for-the-badge&logo=bugsnag" alt="Signaler un Bug">
</a>
</p>
</div>
⚠️ Avertissement
ip-nose est un outil d'information. Son utilisation doit respecter les lois en vigueur.
<p align="center">
Fait avec ❤️ par Karim
</p>

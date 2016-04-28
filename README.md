# 42-ft_nmap

Le but du sujet est de vous faire recoder une partie du programme nmap et ainsi
découvrir une nouvelle bibliothèque très puissante.
Vous allez aussi devoir utiliser les threads dans le but de diminuer drastiquement le temps
pour scanner les ports choisis.

gestion DNS/version
Flag pour passer au dessus des IDS/firewall.

-n/-R					Ne jamais résoudre les noms DNS/Toujours résoudre [résout les cibles actives par défaut]
-O						Active la détection d'OS
-S						Usurpe l'adresse source
-ttl <num>				Spécifie le champ time-to-live IP
--data-length <num>		Ajoute des données au hasard aux paquets émis

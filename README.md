Décompresser l'archive avec :
    
    -7zip ou Rar sur Windows
    -tar zxvf archive.tgz dans un terminal Linux ou MacOs

Puis dans un shell Unix :
    
    -WSL (cd /mnt/c pour accéder au répertoire C:) ou Virtualbox linux (dossiers partagés) sous Windows
    -terminal pour Linux ou MacOs

Compiler avec make
puis éxécuter ./automaton fichier.aut

Si le fichier est reconnu, entrer les caractères souhaités, 10 entrées sont autorisées;

fichier.aut devant retourner Accepte si le mot est reconnu, Rejette sinon.

Si ./automaton fichier.aut est utilisé , le graphe de l'automate est écrit dans fichier.dot.

Pour visualiser le graphe dans fichier.png, éxécuter:
    -> chmod 740 graphes.sh 



# Automate

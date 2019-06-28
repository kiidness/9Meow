# 9Meow

## Auteurs

- Aurélien Douard
- Eliott Chaput

## Descriptif

9Meow permet de voir des images de chat en fonction de leur race et de les voter.

## Usage

Il suffit de lancer l'application en ayant une connection internet active.

## Techniques de programmation utilisées

### QNetworkAccessManager

9meow utilise QNetworkAccessManager pour faire ses appels d'api asynchrone. Pour récupérer les races de chats, les images et les votes.

### QObject avec QProperties
Chaque category ou catimage est un QObject avec plusieurs propriétés. La modification d'une des propriétés entraîne son rafraîchissement dans les listes (pour le vote des images).

### Listes imbriquées
L'application a 2 listes imbriquées (Master et detail en liste également).

### ListView
La liste des races / catégories s'appuie sur un modèle C++ qui contient une liste de QObject. Elle n'est pas éditable et est chargée automatiquement grâce à l'api.

La liste des images de chat s'appuie sur un modèle C++ qui contient une liste de QObject. Elle n'est pas éditable et est chargée automatiquement grâce à l'api. L'utilisateur peut cependant demander de rafraîchir cette liste ou de charger plus d'images de chats via le PullDownMenu et le PushUpMenu.
Elle contient également les votes qui sont chargés et traités par l'api à l'aide d'un objet C++ consacré aux votes uniquement.

### PullDownMenu

Un PullDownMenu est présent dans la page de la liste des images. Il permet de rafraîchir la liste des images.

### PushUpMenu
Un PushUpMenu est présent dans la page de la liste des images. Il permet de charger d'avantages d'images.

### Clic
Un clic sur une race / catégorie charge des images de chats que vous pouvez votez positivement ou négativement.

## Detail: Vote
Vous ne pouvez voter qu'une seule fois pour un même chat. Le vote se bloque lorsque vous avez voté.


### Options + Sauvegarde (QSettings)
La sauvegarde des votes est réalisé via l'API.

## Bugs connus
- Pas de chargement de liste si pas d'internet.

## Précisions
- +1 si vous aimez les chats (sauf ceux sans poils).

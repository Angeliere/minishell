# LISTE DE TESTS POUR MINISHELL

## Comment utiliser cette liste

1. Compilez votre minishell: `make`
2. Lancez-le: `./minishell`
3. Testez chaque commande ci-dessous
4. Comparez avec le résultat attendu

---

## 📋 SECTION 1: BUILTINS DE BASE

### Test 1.1: echo simple
```bash
echo hello
```
**Attendu:** `hello`

### Test 1.2: echo avec plusieurs arguments
```bash
echo hello world test
```
**Attendu:** `hello world test`

### Test 1.3: echo avec flag -n
```bash
echo -n test
```
**Attendu:** `test` (sans retour à la ligne)

### Test 1.4: echo avec plusieurs -n
```bash
echo -n -n -n hello
```
**Attendu:** `hello` (sans retour à la ligne)

### Test 1.5: pwd
```bash
pwd
```
**Attendu:** Chemin du répertoire courant

### Test 1.6: cd vers home
```bash
cd
pwd
```
**Attendu:** Votre $HOME

### Test 1.7: cd vers /tmp
```bash
cd /tmp
pwd
```
**Attendu:** `/tmp`

### Test 1.8: cd vers répertoire inexistant
```bash
cd /directory_that_does_not_exist
```
**Attendu:** Message d'erreur

### Test 1.9: env
```bash
env
```
**Attendu:** Liste de toutes les variables d'environnement

### Test 1.10: env | grep HOME
```bash
env | grep HOME
```
**Attendu:** Ligne contenant HOME=...

---

## 🔄 SECTION 2: EXPANSION DE VARIABLES

### Test 2.1: Variable HOME
```bash
echo $HOME
```
**Attendu:** Votre répertoire home (ex: `/home/username`)

### Test 2.2: Variable USER
```bash
echo $USER
```
**Attendu:** Votre nom d'utilisateur

### Test 2.3: Variable PATH
```bash
echo $PATH
```
**Attendu:** Votre PATH complet

### Test 2.4: Variable inexistante
```bash
echo $VARIABLE_QUI_NEXISTE_PAS
```
**Attendu:** ` ` (chaîne vide)

### Test 2.5: Plusieurs variables
```bash
echo $USER $HOME
```
**Attendu:** `username /home/username`

### Test 2.6: Variable au milieu du texte
```bash
echo Hello $USER how are you
```
**Attendu:** `Hello username how are you`

### Test 2.7: Variable répétée
```bash
echo $USER $USER $USER
```
**Attendu:** `username username username`

---

## 💲 SECTION 3: VARIABLES SPÉCIALES

### Test 3.1: Exit status après succès
```bash
echo test
echo $?
```
**Attendu:** 
```
test
0
```

### Test 3.2: Exit status après échec
```bash
/bin/false
echo $?
```
**Attendu:** `1` (ou autre code non-zéro)

### Test 3.3: Exit status après commande inexistante
```bash
command_that_does_not_exist
echo $?
```
**Attendu:** `127`

### Test 3.4: PID du shell
```bash
echo $$
```
**Attendu:** Un nombre (PID)

### Test 3.5: Plusieurs fois $$
```bash
echo $$ $$
```
**Attendu:** Même PID deux fois

### Test 3.6: Chaîne d'exit status
```bash
/bin/true
echo $?
/bin/false
echo $?
echo test
echo $?
```
**Attendu:**
```
0
1
test
0
```

---

## 🔤 SECTION 4: GESTION DES QUOTES

### Test 4.1: Single quotes bloquent l'expansion
```bash
echo '$HOME'
```
**Attendu:** `$HOME`

### Test 4.2: Double quotes permettent l'expansion
```bash
echo "$HOME"
```
**Attendu:** `/home/username`

### Test 4.3: Mix de quotes
```bash
echo '$HOME' "$USER" $PATH
```
**Attendu:** `$HOME username /usr/bin:...`

### Test 4.4: Variable dans single quotes
```bash
echo 'User: $USER'
```
**Attendu:** `User: $USER`

### Test 4.5: Variable dans double quotes
```bash
echo "User: $USER"
```
**Attendu:** `User: username`

### Test 4.6: Single quotes vides
```bash
echo ''
```
**Attendu:** ` ` (ligne vide)

### Test 4.7: Double quotes vides
```bash
echo ""
```
**Attendu:** ` ` (ligne vide)

### Test 4.8: Texte avec single quotes
```bash
echo 'hello world'
```
**Attendu:** `hello world`

### Test 4.9: Texte avec double quotes
```bash
echo "hello world"
```
**Attendu:** `hello world`

### Test 4.10: Quotes imbriquées (simples dans doubles)
```bash
echo "It's working"
```
**Attendu:** `It's working`

### Test 4.11: $? dans single quotes
```bash
echo '$?'
```
**Attendu:** `$?`

### Test 4.12: $? dans double quotes
```bash
echo "$?"
```
**Attendu:** `0` (ou dernier exit code)

---

## 🔧 SECTION 5: EXPORT ET UNSET

### Test 5.1: Export simple
```bash
export TEST=hello
echo $TEST
```
**Attendu:** `hello`

### Test 5.2: Export avec plusieurs variables
```bash
export VAR1=one VAR2=two
echo $VAR1 $VAR2
```
**Attendu:** `one two`

### Test 5.3: Export sans valeur
```bash
export EMPTY_VAR
echo $EMPTY_VAR
```
**Attendu:** ` ` (vide)

### Test 5.4: Unset variable
```bash
export TO_DELETE=value
echo $TO_DELETE
unset TO_DELETE
echo $TO_DELETE
```
**Attendu:**
```
value

```

### Test 5.5: Export puis réutiliser
```bash
export NAME=Alice
echo Hello $NAME
echo Welcome $NAME
```
**Attendu:**
```
Hello Alice
Welcome Alice
```

---

## ⚠️  SECTION 6: ERREURS DE SYNTAXE

### Test 6.1: Pipe au début
```bash
| echo test
```
**Attendu:** Erreur de syntaxe

### Test 6.2: Pipe à la fin
```bash
echo test |
```
**Attendu:** Erreur de syntaxe

### Test 6.3: Double pipe
```bash
echo test || echo test2
```
**Attendu:** Erreur de syntaxe

### Test 6.4: Redirection sans fichier
```bash
echo test >
```
**Attendu:** Erreur de syntaxe

### Test 6.5: Double redirection sans fichier entre deux
```bash
echo test > >
```
**Attendu:** Erreur de syntaxe

---

## 🔀 SECTION 7: REDIRECTIONS (si implémentées)

### Test 7.1: Redirection output
```bash
echo hello > /tmp/test_minishell.txt
cat /tmp/test_minishell.txt
```
**Attendu:** `hello`

### Test 7.2: Redirection append
```bash
echo line1 > /tmp/test_append.txt
echo line2 >> /tmp/test_append.txt
cat /tmp/test_append.txt
```
**Attendu:**
```
line1
line2
```

### Test 7.3: Redirection input
```bash
echo test > /tmp/test_input.txt
cat < /tmp/test_input.txt
```
**Attendu:** `test`

### Test 7.4: Redirection vers fichier inexistant
```bash
cat < /file_that_does_not_exist
```
**Attendu:** Erreur

---

## 🚰 SECTION 8: PIPES (si implémentés)

### Test 8.1: Pipe simple
```bash
echo hello | cat
```
**Attendu:** `hello`

### Test 8.2: Pipe avec grep
```bash
env | grep HOME
```
**Attendu:** Ligne avec HOME=...

### Test 8.3: Multiple pipes
```bash
echo test | cat | cat | cat
```
**Attendu:** `test`

### Test 8.4: Pipe avec wc
```bash
echo "hello world" | wc -w
```
**Attendu:** `2`

---

## 🎯 SECTION 9: CAS COMPLEXES

### Test 9.1: Variable avec underscore
```bash
export MY_VAR=test
echo $MY_VAR
```
**Attendu:** `test`

### Test 9.2: Variable avec chiffres
```bash
export VAR123=value
echo $VAR123
```
**Attendu:** `value`

### Test 9.3: Plusieurs espaces
```bash
echo hello    world
```
**Attendu:** `hello world`

### Test 9.4: Tabulations
```bash
echo hello	world
```
**Attendu:** `hello world`

### Test 9.5: Espaces au début
```bash
   echo test
```
**Attendu:** `test`

### Test 9.6: Espaces à la fin
```bash
echo test   
```
**Attendu:** `test`

### Test 9.7: Ligne vide
```bash

```
**Attendu:** (retour au prompt)

### Test 9.8: Juste des espaces
```bash
     
```
**Attendu:** (retour au prompt)

---

## 🧪 SECTION 10: EDGE CASES

### Test 10.1: Dollar seul
```bash
echo $
```
**Attendu:** `$`

### Test 10.2: Plusieurs dollars
```bash
echo $$$$
```
**Attendu:** (PID répété)

### Test 10.3: Variable après texte
```bash
echo test$HOME
```
**Attendu:** `test/home/username`

### Test 10.4: Variable avant texte
```bash
echo $HOMEtest
```
**Attendu:** ` ` (variable HOMEtest n'existe pas)

### Test 10.5: Quote unique non fermée (devrait attendre)
```bash
echo 'test
```
**Attendu:** Attend la fermeture ou erreur

### Test 10.6: Quote double non fermée
```bash
echo "test
```
**Attendu:** Attend la fermeture ou erreur

---

## 🔚 SECTION 11: EXIT

### Test 11.1: Exit simple
```bash
exit
```
**Attendu:** Ferme le minishell

### Test 11.2: Exit avec code
```bash
exit 42
```
**Attendu:** Ferme avec code 42

### Test 11.3: Exit avec argument invalide
```bash
exit abc
```
**Attendu:** Erreur ou comportement défini

---

## 📊 SECTION 12: SIGNAUX

### Test 12.1: Ctrl+C pendant la saisie
- Tapez du texte
- Appuyez sur Ctrl+C
**Attendu:** Nouvelle ligne de prompt, texte effacé

### Test 12.2: Ctrl+D sur ligne vide
- Ne tapez rien
- Appuyez sur Ctrl+D
**Attendu:** Ferme le shell (comme exit)

### Test 12.3: Ctrl+\ (SIGQUIT)
- Appuyez sur Ctrl+\
**Attendu:** Ignoré (pas de "Quit")

---

## ✅ CHECKLIST RAPIDE

Cochez au fur et à mesure:

- [ ] Echo fonctionne
- [ ] Pwd fonctionne
- [ ] Cd fonctionne
- [ ] Env fonctionne
- [ ] $HOME s'expand
- [ ] $USER s'expand
- [ ] $? fonctionne
- [ ] $$ fonctionne
- [ ] Single quotes bloquent expansion
- [ ] Double quotes permettent expansion
- [ ] Export fonctionne
- [ ] Unset fonctionne
- [ ] Erreurs de syntaxe détectées
- [ ] Redirections fonctionnent
- [ ] Pipes fonctionnent
- [ ] Ctrl+C fonctionne
- [ ] Exit fonctionne

---

## 🎯 SCORE MINIMUM POUR VALIDER

- **Obligatoire (minishell de base):** Tous les tests Sections 1-6
- **Recommandé:** Sections 7-9
- **Bonus:** Sections 10-12

**Bonne chance avec vos tests!** 🚀

# Updating your TrkAna v5 area to an EventNtuple v6 area

Rename your own fork on GitHub. Go to settings and change the repository name under "General"

From your working directory before doing ```muse setup```:

```
mv TrkAna/ EventNtuple/
cd EventNtuple/
git remote set-url origin git@github.com/YourUsername/EventNtuple
git remote set-url mu2e https://github.com/Mu2e/EventNtuple
cd ../
rm -rf build/XXX/ # if you like
mu2einit
muse setup

muse build -j4 --mu2eCompactPrint
```


# 3rd party

This directory contains 3rd-party libs.

## Manual subtree strategy

After reading [this article](https://medium.com/@porteneuve/mastering-git-subtrees-943d29a798ec), I've decided to use the **manual** method of adding a subtree, not the `subtree` script available in `git`.

Here is a simple example of how `qt-supermacros` was cloned:

```sh
git remote add qt-supermacros http://gitlab.unique-conception.org/qt-qml-tricks/qt-supermacros.git
git fetch qt-supermacros
git read-tree --prefix=3rdparty/qt-supermacros -u qt-supermacros/master
git commit -m "added subtree http://gitlab.unique-conception.org/qt-qml-tricks/qt-supermacros in 3rdparty/qt-supermacros"
```

## List of libraries

* [qt-supermacros](http://gitlab.unique-conception.org/qt-qml-tricks/qt-supermacros.git)
* [qt-qml-models](http://gitlab.unique-conception.org/qt-qml-tricks/qt-qml-models.git)

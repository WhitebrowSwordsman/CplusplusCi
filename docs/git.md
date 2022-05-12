# git笔记

## commit

### 本地合并多个commit到一个commit
1. 在这个例子中，我们将压缩最后 3 次提交。 并且**强制**推送到远端。
   ```bash
   git reset --soft HEAD~3 && git commit
   git push --force origin HEAD
   ```

### 丢弃本地commit
1. 比如丢弃这个`0d1d7fc32`: `git reset --hard 0d1d7fc32`
2. 丢弃多次本地commit: `git reset --hard HEAD~2`

## Github

### 创建tag

1. 在当前分支创建tag: `git tag <tagname>`
2. 推送tag到远端仓库: `git push origin --tags`

### 删除tag
1. 删除远端仓库tag: `git push --delete origin <tagname>`
2. 删除本地tag: `git tag -d <tag_name>`

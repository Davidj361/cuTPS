# cuTPS
---

## Git Setup

1. Set your name `git config --global user.name "John Doe"`
2. Set your email `git config --global user.email johndoe@example.com`
3. Optional, set some other settings
  - `git config --global color.status auto`
  - `git config --global color.branch auto`
  - `git config --global color.interactive auto`
  - `git config --global color.diff auto`

For all Git related issues see this [site](http://git-scm.com/doc).  Don't be lazy, read and google. 
There's LOTS of documentation.

## Repository setup

1. Make sure you have [SSH keys](https://gitlab.com/profile/keys) setup. [Help](https://gitlab.com/help/ssh/ssh)
2. Create project directory
3. Initialize the repository `git init`
4. Set the remote repository you want to track and call it origin `git remote add origin git@gitlab.com:team-do-not-stick-in-ear/cutps.git`
5. Pull the files from the master branch on origin to your local machine `git pull origin master`
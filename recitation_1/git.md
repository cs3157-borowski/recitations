# Git for AP Workflow

Git is a version control system designed for source code and other kinds of plain text. It is great for synchronizing work when you are working in a team, as well as keeping track of changes you make when you are working alone.

In this class, you are **required to use Git for your homework assignments.** You use it to obtain skeleton code, document your progress, and submit your work. You can also use Git to view my solutions, once I release them.

Git is first and foremost a command-line tool, invoked using the "git" command. "git" actually encompasses a number of subcommands, such as "git clone", "git pull", and "git checkout".
You can see the man pages for each subcommand using the --help flag:

	$ git clone --help  # brings up the man pages for git clone
	$ man git-clone     # does the same as above


## What is a Git Commit?
Starting with the Git commit – the most integral part of using Git as a workflow manager. 

Commits are "snapshots" of your code throughout the various stages of development. Most git commands are oriented around updating and interacting with git commits, commands that we will go over below.

## Checking-out a Repository and Getting Skeleton Code
Now that we have established what Git and Git commits are, we can go ahead and start this demo! 

1. Check your email for an invitation on the **"cs3157-borowski-s23/hw#-team#"** repository and accept the invitation. 
2. Now, sign-in to GitHub.com, go to the top right profile icon and click 'Your Organizations'. You should see **"cs3157-borowski-s23"** listed as one of them, click on that and find the repository that corresponds with the assignment number that we are on (ie: hw1-team1) and click on that
3. This is **your remote repository** that you are collaborating on with your partner.

You should see all the neccessary skeleton code that we distribute for the assignment. This your remote repository, and now we need to create your **local repository** in order for you to actually work on the assignment. 

1. Click the green "<> Code button, make sure you have selected 'SSH' and copy that link.
2. Using whatever interface you configured and go to the command-line and run `git clone <pasted-link>` 
3. If that was successful, you now have a **local repository**. 

## Repository Structure 
Git manages multiple copies of your local repo’s contents:

1. the working directory is what you can see and edit, i.e., outside of .git/
2. the staging area (AKA "index") is what will form the next commit
3. each commit has a snapshot of your repo’s contents at some point in time

Git also keeps **HEAD**, which is a reference to your repo's most recent commit, aka staged **and** committed revision to your repo.

Thus, there are also multiple copies of each (tracked) file in your repo.

Git uses some clever tricks to make sure that identical copies of the same file don’t take up unnecessary space (beyond the scope of this lecture).

Note that when you clone a repo, you will only receive its commit history; modifications in the working directory and staging area are not cloned.

## File States in Local Repository
In the Git Repository, files can be in the following states:

1. **Untracked**: files that are not under Git revision control, a little deceiving.
2. **Tracked, unmodified**: the file is in the Git repository, and it has not been modified since the last commit.
3. **Tracked, modified, but unstaged**: this is a file that is under Git revision, you have made changes but have not staged these changes.
4. **Tracked, modified, and staged**: this is a file under Git revision, you made changes, and staged these changes.

## HEAD, Staging Area, and Working Directory Flow
A fresh clone is ready to be worked on. Your 

1. The **HEAD** refers to the most recent revision, which is the last commit (the skeleton code if you just cloned). Git uses the HEAD as a reference for changes made to your local repository files.
2. As you code and make changes to the files, they are saved in the **working directory**. At this point, the HEAD (last commit) and the working directory differ.
3. To save the changes in the working directory and reflect them in the last commit, you need to stage them in the **staging area**.
4. Committing to the changes in the staging area updates the latest commit, making the **HEAD** refer to this latest commit.

You might be picking up this is a cycle, and that is because it is! You are editing and revising files and using that revision for the next edit and revision. 

## Piecing this All together 
It is important to know the difference between status of files that are in our **working directory** vs. the **staging area** 

1. Working Directory:

	I. **Untracked**: files that are not under Git revision control, these are files that were not part of skeleton code (IE: Executeables or files you created)

	II. **Tracked, unmodified**: the file is in the Git repository, and it has not been modified since the last commit.

	III. **Tracked, modified, but unstaged**: this is a file that is under Git revision, you have made changes but have not staged these changes.

2. Staging Area: 

	I. **Tracked, modified, and staged**: this is a file under Git revision, you made changes, and staged these changes.

## Working Responsibly in Git -- Branching
**With or without a group**, there is definitely a *right* way to use Git that would maxmize it's many features that make Git a great workflow manager. Branching is **highly reccomended** when completing the assignments (especially for those of you in a pair)

- Git branches allow you to create **multiple streams of development within the same repository**. Each branch has its own **HEAD**, which points to the latest commit in that branch. 

- When you create a new branch, it starts from the same place as the branch you created it from. You can then make separate commits to the new branch without affecting the original branch. 

- This makes it easy to isolate and manage different changes. When you're ready, you can merge the changes in your feature branch back into the original branch.

Make sure you are in your local repository and run `~$git branch` it should say `* master` with the aterick indicating that you are on the master branch. 

To make a new branch (don't be scared) run `git branch <insert-branch-name>`. Now run `git branch -a ` to see all the branches. 

Branches are made in your **local repository** and each branch is a copy of your local repository. To move to another branch and start coding on that branch, run `git checkout <insert-branch-name>`. You should see `Switched to branch '<insert-branch-name'>`. You can now start developing! 


## Let's Start Coding (finally)! 
Whether working with a gYes, finally! Passed all the terminology we are going to get into the commands. We are going to go through the commands as they would need to be used as you are writing code. 

 1. You edit the skeleton file (`vim <filename>`) and you made great progress! These are edits that only exist in your working directory. 
 2. Run `git status`, this is a command that tells you the state of your working directory relative to last commit (**HEAD**). 
 3. Maybe you are having some second guesses, you are nervous! You want to review the differences between the last commit and your working director. Run `git diff` to show you these changes. 
 4. You are sure of these changes, and you want to commit them, let's stage these files that are changed. Run `git add <file-name>` to stage these files for commit
 5. Assure that all the changes to the files you want to commit are in the staging area –listed under the "Changes to be committed" when you run `git status`
 6. You are ready to 'commit' to these changes! Run `git commit -m "<insert-short-message>"` You have made commit, this now becomes **HEAD** of this branch and is the latest revision of your local repository on **your branch**. This commit and all these changes will become the baseline of comparison that Git will use to recgonize further changes. 
 7. Run `git log` to show your most recent commit as well as your commit history

### Some Notes

1. Remember you committed these changes onto ***your specific branch***
2. Unlike `git add`, `git commit` status doesn't require you to specify specifc files to commit, that is because `git commit` commits all the files that you staged
2. Try to make meaningful messages when you run `git commit` as they might be helpful for remmebering what you did at each commit

**Check for understanding:** After you commit but do not make changes to your file, is it possible to have unstaged and uncommitted changes in your working directory? 


## Local to Remote Repository
There are a lot of layers of comparison that Git is responible for managing. Let's take a look: 
1. Differences between files in your **working directory** the **staging area** and the last commit, **HEAD** 
2. Differences between branches in the your **local repository** 
2. Finally, differences between your **local** and **remote repository**

Let's begin to reconcile these differences step by step. Starting with #2 (since we went over #1 above). If you were following closely (which we really hope you are) this process is quite simple though you to resolve a lot of these differences. 

1. Since your branch is created from your local repository, you will need to 'upload' your branch to your remote repository. Run `git push origin <insert-branch-name>`
2. Now, go back to your remote repository (github.com) and refresh the page, you should see in a yellow-box 'Compare & pull request'. 

What is a pull request? 

## Pull Requests 
Pull requests are great for those of you that are working in pairs but even for those of you that are working alone they can be incredibly helpful. Pull requests erssentially allow you to propoes the changes that you made on your own branch to be merged with another, probably, master branch. 

If you clicked 'Compare & pull request', you should be prompted to create a title and leave a comment for your pull request. ***Everyone*** in your repository will see this. This pull request allows other members to see the changes you made on your branch (that you cloned from the master branch) and decide whether they want to **merge** these changes onto the **master branch**. 

It is best practice that you run and test your code before you make your PR, as your can assure that your master branch is good-functioning code and your sub-branches are for developing. You and your partner can be working on different parts on the code on different branches, push your branches, and make pull requests to merge to the **master branch** which you will tag and the TA's will grade. 

Sounds simple, and sometimes it is! But there are times that you will run into **merge conflicts** when trying to merge a sub-branch and master branch. 

PR are a great tool, read more about them [here](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests). 

## Problems That May Arise

1. 

# *edits end here*






### Working Directory to Staging Area
You made some changes to your local repository in your working directory. Using `~$git status`, git will show you the files that you have changed using HEAD as a point of refrence for these changes. At this point, you can precisely see what changes you made using `~$ git diff` to see the difference between HEAD (reference to last commit) and your working directory. Now, let's stage these changes and prepare them for a future commit. Using `~$git add <filename(s)>` you can move these changes in your working directory to the staging area. Try running `~$git status` after, you will see that git reports that you have staged changes and are ready to commit.   

1. `~$git status` - Shows differences from the result of changes in your working directory from the HEAD reference 
2. `~$git diff` - Shows those exact differences between the HEAD reference and working directory
3. `~$git add <filename(s)> //Yes! You can stage multiple files at once `- Moves changes that were made in working directory to the staging area

### Staging Area to HEAD 
You are now in the staging area and you want to save these changes. This step *updates* the HEAD reference ane makes these changes part of your repository's history. Using `~$git commit -m <short-message>` you are commiting your changes 

```
~$ git status
```
Reports if there are changes to be staged and/or committed to your local repository. 
```
~$ git log
```
Shows entire commit history. 

```
~$ git add <filename>
```
Move files in working directory to the staging area, ready to commit changes to local repository. 
```
- '~$ git commit -m "<commit message>"'

- git add: add changed files to the staging area
- git commit: create a commit from changes checked into the staging area
- git tag: mark an important milestone
- git push: push commits to a remote repo
- git pull: pull changes from a remote repo
- git clone: obtain a copy of another repo with its commit history

Anatomy of a repository -----------------------

Git organizes collections of files as repositories (aka "repos"):

- A repo is always "rooted" in some directory; all "tracked" files must live within that directory tree.

- Repos keep track of the version history of their files in a "commit log" (AKA "commit history").

- Each Git repo contains a special, hidden .git/ directory where the commit history and other metadata is stored.

You can run Git commands from any subdirectory within a repo.

From working directory to commit --------------------------------

Git manages multiple copies of your repo’s contents:

- the working directory is what you can see and edit, i.e., outside of .git/
- the staging area (AKA "index") is what will form the next commit
- each commit has a snapshot of your repo’s contents at some point in time

Thus, there are also multiple copies of each (tracked) file in your repo.

A file is tracked if it is in the staging area or in some commit.  When you git add a file, you copy it from your working directory to the staging area.

The most recent commit in your repo is known as HEAD.  When you git commit, you create a new commit (now the new HEAD) from the contents of your staging area.

`                        `git add                  git commit

`    `working directory ----------> staging area -------------> HEAD

`                                                         `(commit history)

Git uses some clever tricks to make sure that identical copies of the same file don’t take up unnecessary space (beyond the scope of this lecture).

Note that when you clone a repo, you will only receive its commit history; modifications in the working directory and staging area are not cloned.

The Git file life cycle -----------------------

git status will tell you when there are differences between the copies of a file in the working directory, the staging area, and HEAD.  This is helpful for

keeping track of which modifications end up in your next commit.  The output of git status usually looks something like this:

	$ git status
	Changes to be committed:
		modified:   foo.txt
	Changes not staged for commit:
		modified:   bar.txt
	Untracked files:
		baz.txt

These sections are to be interpreted as follows:

1) If a file appears in the "Untracked files" section like baz.txt, then it only exists in your working directory, and is not yet tracked in the staging area or commit history.

2) If a file appears in the "Changes to be committed" section like foo.txt, then the staged copy of that file differs from the copy in HEAD.
2) If a file appears in the "Changes not staged for commit" section like bar.txt, then the working copy of that file differs from its staged copy.

4) If a file does not appear in any of these sections, then the working, staged, and HEAD copies of that file are identical.

It is sometimes helpful to think of these statuses as stages in the life cycle of each file tracked by Git:

![git.png](../images/git.png)

Note that it is possible for a file to have both staged (2) and unstaged (3) changes, i.e., if it has been modified since it was git added.  The life cycle diagram does not illustrate this scenario.

.gitignore files (optional) ---------------------------

There are often files that you don’t ever want to track in a repo.  For example, it is considered bad practice to track object files and executables (you will learn about these in a later lecture).  It can be cumbersome to see them in your git status, and it’s easy to accidentally track these files.

You can use a .gitignore file to tell Git that you don’t want to track a file. For example, this .gitignore tells Git not to track any files named "a.out", or whose file name ends with ".o":

	$ cat .gitignore a.out
	\*.o

Any files matching those rules will not show up in git status, nor will they be tracked when you git add them.  These .gitignore rules only apply to directory the .gitignore file is in, and any of its subdirectories.  You can place

different .gitignore files in different directories to ignore files more selectively.  You can read the man pages (man gitignore) for more usage details.

It is considered good practice to include .gitignore files in your Git repos. You should also track .gitignore files themselves in your repo, since the same .gitignore rules will likely apply to any others who clone your repo.

Anatomy of a commit -------------------

We refer to each commit by its "commit hash", which is a long string of characters computed from the following information:

- the file contents of the commit
- the commit message (e.g., git commit -m "the commit message")
- the author and timestamp of the commit
- its parent commit(s), i.e., the previous commit(s) in the commit history

If any of these change, the commit hash will also change.

When you git commit, the old HEAD will become the parent commit of the new HEAD. For this course, we will only work with repos with a linear commit history:

where each commit has a single parent, and where each parent has one child.

It is possible for a commit to have multiple children if different commits are made with the same parent.  You will often encounter such divergent commit histories when using Git to collaborate with others.  You have two options in order to join a divergent history:

- create a merge commit, i.e., a commit with multiple parent commits
- rebase one set of commits onto another, modifying their commit hashes

When you do either of these, Git will try to automatically merge the different sets of changes, but will stop and ask you to resolve merge conflicts if it encounters any.

Other useful Git commands -------------------------

- git ls-files: list tracked files
- git mv/rm: rename or remove a tracked file
- git diff: see changes between the working directory and staging area
- git diff --cached: see changes between the staging area and HEAD
- git diff HEAD: see changes between the working directory and HEAD
- git restore: restore file in working directory from staging area
- git restore --staged: restore file in staging area from HEAD

## Other Git Resources

There are plenty of hands-on guides teaching you how to use Git.
Here are a few we recommend for getting started:

- man gittutorial: the official Git tutorial included in its man pages
- git - the simple guide (https://rogerdudler.github.io/git-guide/):

a guide that gets straight to the point with nice illustrations

- Yet Another Git Guide (https://j-hui.com/pages/yagg/):

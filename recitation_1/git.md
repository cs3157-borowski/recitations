# **Git for AP Workflow**

Git is a version control system designed for source code and other kinds of plain text. It is great for synchronizing work when you are working in a team, as well as keeping track of changes you make when you are working alone.

In this class, you are **required to use Git for your homework assignments.** You use it to obtain skeleton code, document your progress, and submit your work. You can also use Git to view my solutions, once I release them.

Git is first and foremost a command-line tool, invoked using the "git" command. "git" actually encompasses a number of subcommands, such as "git clone", "git pull", and "git checkout".
You can see the man pages for each subcommand using the --help flag:

	$ git clone --help  # brings up the man pages for git clone
	$ man git-clone     # does the same as above

Take this as a guide of **limited** use of Git and not ***AP-specific*** as these commands and workflow are used everywhere. Using Git is a great skill to build for those of you who plan on continuing to code at Columbia andbeyond. 

# Understanding the Basics of Git


## What is a Git Commit?
Starting with the Git commit – the most integral part of using Git as a workflow manager. 

Commits are "snapshots" of your code throughout the various stages of development. Most git commands are oriented around updating and interacting with git commits, commands that we will go over below.

## Remote Repository and Skeleton Code
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

Thus, there are also multiple copies of each (tracked) file in your repo. Git will use these multiple copies to automatically track changes between copies (IE: differences between the most committed version and files in the working directory)

**Note**: when you clone a repo, you will only receive its commit history; modifications in the working directory and staging area (files that are un-staged and non-committed) are not cloned.

## File States in Local Repository
In the Git Repository, files can be in the following states:

1. **Untracked**: files that are not under Git revision control, a little deceiving.
2. **Tracked, unmodified**: the file is in the Git repository, and it has not been modified since the last commit.
3. **Tracked, modified, but unstaged**: this is a file that is under Git revision, you have made changes but have not staged these changes.
4. **Tracked, modified, and staged**: this is a file under Git revision, you made changes, and staged these changes.


## Piecing this All together 
It is important to know the difference between status of files that are in our **working directory** vs. the **staging area** 

### HEAD, Staging Area, and Working Directory Flow
Your fresh clone is ready to be worked on. Referring back to git repository structure, let's look at that one more time. 

1. The **HEAD** refers to the most recent revision, which is the last commit (the skeleton code if you just cloned). Git uses the HEAD as a reference for changes made to your local repository files.
2. As you code and make changes to the files, they are saved in the **working directory**. At this point, the HEAD (last commit) and the working directory differ.
3. To save the changes in the working directory and reflect them in the last commit, you need to stage them in the **staging area**.
4. Committing to the changes in the staging area updates the latest commit, making the **HEAD** refer to this latest commit.

You might be picking up this is a cycle, and that is because it is! You are editing and revising files and using that revision for the next edit and revision. 

1. Working Directory:

	I. **Untracked**: files that are not under Git revision control, these are files that were not part of skeleton code (ie: executeables or files you created not included when you cloned remote repo)

	II. **Tracked, unmodified**: the file is in the Git repository, and it has not been modified since the last commit.

	III. **Tracked, modified, but unstaged**: this is a file that is under Git revision, you have made changes but have not staged these changes.

2. Staging Area: 

	I. **Tracked, modified, and staged**: this is a file under Git revision, you made changes, and staged these changes.

# Working Responsibly in Git – Branching
**With or without a group**, there is definitely a *right* way to use Git that would maxmize its many features that make Git a great workflow manager. Branching is **highly reccomended** when completing the assignments (especially for those of you in a pair)

### Branching Overview

- Git branches allow you to create **multiple streams of development within the same repository**. Each branch has its own **HEAD**, which points to the latest commit in that branch. 

- When you create a new branch, it starts from the same place as the branch you created it from. You can then make separate commits to the new branch without affecting the original branch. 

- This makes it easy to isolate and manage different changes. When you're ready, you can merge the changes in your feature branch back into the original branch.

Make sure you are in your local repository and run `~$git branch` it should say `* master` with the aterick indicating that you are on the master branch. The master branch is the **default branch**, but Git also supports **main** as a default branch name as well.  

To make a new branch (don't be scared) run `git branch <insert-branch-name>`. Now run `git branch -a ` to see all the branches. 

Branches are made in your **local repository** and each branch is a copy of your local repository. To move to another branch and start coding on that branch, run `git checkout <insert-branch-name>`. You should see `Switched to branch '<insert-branch-name'>`. You can now start developing! 

### **Review: Git Commands for Branching** 
1. `~$ git branch` shows the branch that you are currently working on in your local repo
2. `~$ git branch -a` lists all the branches in your local repo 
3. `~$ git branch <branch-name>` creates a branch named "<branch-name>" 
4. `~$ git checkout  <branch-name>` allows you to 'move' to the indicated branch 
5. `~4 git push origin <branch-name>` pushes your local branch to your remote repo as well as all the commits you made on that branch 

# Let's Start Coding (finally)! 
Passed all the terminology we are going to get into the commands. We are going to go through the commands as they would need to be used as you are writing code. 

 1. You edit the skeleton file (`vim <filename>`) and you made great progress! These are edits that only exist in your working directory. 
 2. Run `git status`, this is a command that tells you the state of your working directory relative to last commit (**HEAD**). 
 3. Maybe you are having some second guesses, you are nervous! You want to review the differences between the last commit and your working director. Run `git diff` to show you these changes. 
 4. You are sure of these changes, and you want to commit them, let's stage these files that are changed. Run `git add <file-name>` to stage these files for commit
 5. Assure that all the changes to the files you want to commit are in the staging area –listed under the "Changes to be committed" when you run `git status`
 6. You are ready to 'commit' to these changes! Run `git commit -m "<insert-short-message>"` You have made commit, this now becomes **HEAD** of this branch and is the latest revision of your local repository on **your branch**. This commit and all these changes will become the baseline of comparison that Git will use to recgonize further changes. 
 7. Run `git log` to show your most recent commit as well as your commit history

### Things to Remember:
1. Remember you committed these changes onto ***your specific branch***
2. Unlike `git add`, `git commit` status doesn't require you to specify specifc files to commit, that is because `git commit` commits all the files that you staged
2. Try to make meaningful messages when you run `git commit` as they might be helpful for remmebering what you did at each commit

 **Q:** After you commit but do not make changes to your file, is it possible to have unstaged and uncommitted changes in your working directory? 
 
 **A:** Yes, you commit only the changes in the files that you staged. However, whatever is unstaged still only exists in the working directory.  

### **Review: Git Commands for Adding and Committing Changes** 
	
1. `~$ git status` compares the last committed version of your repo and the working directory and indicates what stage each file is in
2. `~$ git diff` Git will show you the exact differences between HEAD reference and working directory
3. `~$ git add <filename(s)>` will stage files that have been modified, preparing them to be committed
4. `~$ git commit -m "<short-message>` commits the tracked, modified, and staged files, updates HEAD reference, makes changes the most revent revision of git repo
5. `~$ git log` will show your commit history 
6. `~4 git push origin <branch-name>` pushes your local branch to your remote repo as well as all the commits you made on that branc

# Settling Differences Cetween Commits
Sounds dramatic, but really, Git is tracking alot of differences between versions of your code. Let's take a look: 
1. Differences between files in your **working directory** the **staging area** and the last commit, **HEAD** 
2. Differences between branches in the your **local repository** 
2. Finally, differences between your **local** and **remote repository**

Let's begin to ***reconcile*** these differences step by step. Starting with #2 (since we went over #1 above). If you were following closely (which we really hope you are) this process is quite simple though you to resolve a lot of these differences. 

## Differences Between Two Local Branches

Creating two local branches can be benefitial for various reasons, say you want to preserve two seprate branches that develop different parts of an assignment. That is one example, but whatever it may be, you might also want to **merge** two local branches.

1. Use `~$ git checkout <branch-name` to move to the branch you want (could be either of the two you want to merge)
2. Use `~$ git merge <branch-name>` to merge the two local branches. 
3. You will then use `~$ git commit` to commit this merge, to which you can `~$git push` to push local branch to remote repo
	
## Differences Between a Local and Remote Branch

When working in a pair, you and/or your partner will be making updates to your master branch. Once you cloned your remote repo, it only clones it in the moment you ran `~$ git clone` and does not update if your partner is updating any branch in your remote repo, including master. 
	
1. Using `~$ git fetch` takes care of that discepancy between local and remote repo's, running this command will download the state of the remote repository and **put it into a branch named <remote>:<branch_name>**. This results in two branches: **local master branch** and **one with the most recent committed and pushed changes from GitHub**
	
2. If you want changes rom GitHub to apply to your local branch, `~$ git merge <branch-name>` will merge changes from specified branch and the branch you are on. 

You might be thinking, this sounds familiar. Good, it should! `~$ git pull` combines `~$ git fetch` and `~$ git merge`, but don't always default to pull. **There are times where you might want to seperate these steps.**

## Differences Between a Local Branch and Remote Repo
	
1. Since your branch is created from your local repository, you will need to 'upload' your branch to your remote repository. Run `git push origin <insert-branch-name>`
2. Now, go back to your remote repository (github.com) and refresh the page, you should see in a yellow-box 'Compare & pull request'.

Now, what is a pull request? 

## Pull Requests 
Pull requests are great for those of you that are working in pairs but even for those of you that are working alone they can be incredibly helpful. Pull requests allow you to propoes the changes that you made on your own branch to be merged with another such as the master branch. 

If you clicked 'Compare & pull request', you should be prompted to create a title and leave a comment for your pull request. ***Everyone*** in your repository will see this. This pull request allows other members to see the changes you made on your branch (that you cloned from the master branch) and decide whether they want to **merge** these changes onto the **master branch**. 

In that "Pull request" you are able to look at the changes that your partner changed by clicking "Files changed". You are able to leave comments and questions to which you and your partner can decide to resolve. 

It is best practice that you run and test your code before you make your PR, as your can assure that your master branch is good-functioning code and your sub-branches are for developing. You and your partner can be working on different parts on the code on different branches, push your branches, and make pull requests to merge to the **master branch** which you will tag and the TA's will grade. 

If you (and your partner if applicable) decide to merge, you will make a merge commit, and your now merged (sub and master) will become to the most recent revision of your code. 

Sounds simple, and sometimes it is! But there are times that you will run into **merge conflicts** when trying to merge a sub-branch and master branch. 

PR are a great tool, read more about them [here](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests). 

# Merge Conflicts

If you are working alone or working with a partner, merge conflicts are avoidable but ultimately inevitable (if you don't follow the directions above carefully). But they can be quite frightening. We talked about `~$ git merge <branch-name>` above, but something we did not mention is that merge will automatically try to merge using a fast-forward approach which will succeed **if the changes you are merging do not confict with one another** but will fail otherwise. 

Thus, we encourage that when merging two-local branches and a local branch to your remote reop, to run `~$ git merge` with the `--no-ff` option like this: `~$ git merge --no-ff <branch-name>`. 

Let's see an example of merge conflict. 


### Merge Conflict Example:

	
Conflict may arise if: 
1. Changes to the same line(s) of code in two different branches.
2. Deletions of a file in one branch and changes to the same file in another branch.
3. Deletions of a file in one branch and changes to the same file in another branch.
4. If you have uncommitted changes in your branch and want to merge, this will overwrite your changes in working directory


### **What to Do If you have Merge Conflict?**
Let's trigger a merge conflict.
```bash
UNI@ap:~/cs3157/hw1-team0/src$ git branch -a 
* master 
  your-branch

UNI@ap:~/cs3157/hw1-team0/src$ git checkout your-branch
Switched to branch 'your-branch'
```
Up to this point we have see that there are two branches. In both of those branches we have have a file named **AP.txt** that contains only one line Let's see what that looks like in each branch. Note `cat` is a bash command that when passed a file will output the files contents to the terminal (stdout to be precise). 

```
UNI@ap:~/cs3157/hw1-team0/src$ git checkout master
Switched to branch 'master'

UNI@ap:~/cs3157/hw1-team0/src$ cat AP.txt 
AP teaching staff is the worst :( 
```
Let's see what that file contains in "your-branch":
```
UNI@ap:~/cs3157/hw1-team0/src$ git checkout your-branch
Switched to branch 'your-branch'

UNI@ap:~/cs3157/hw1-team0/src$ cat AP.txt 
AP teaching staff is the best :)
```
Running `~$git merge` will result in a conflict, as Git sees that both branches have committed changes to the same file and the same line. This is where `~$ git merge --no-ff <your branch>` comes in. In the above example, if we ran this command, the file might look something like this (remember we are on the master branch): 

```
UNI@ap:~/cs3157/hw1-team0/src$ cat AP.txt 
<<<<< master
AP teaching staff is the worst :(
======
AP teaching staff is the best :)
>>>>>
```
As you can see, it has both of our changes, so we have to manually decide which one to keep, you would do that by removing the lines that start with <<<< (showing you the state of that line in the branch you are in, the one with the * when you run the git branch command), the one that starts with >>>> (showing you the state of that line in the branch you specified in the git merge <branch> command), and the one that starts with ==== (just a separator), and also the change you don't want to keep, so like this:
```
UNI@ap:~/cs3157/hw1-team0/src$ cat AP.txt 
AP teaching staff is the best :)
```
Then, of course, you would stage and commit the file –– this is what we call a **merge commit**. 

## Other Git Resources

There are plenty of hands-on guides teaching you how to use Git.
Here are a few we recommend for getting started:

- man gittutorial: the official Git tutorial included in its man pages
- git - the simple guide (https://rogerdudler.github.io/git-guide/):

a guide that gets straight to the point with nice illustrations

- Yet Another Git Guide (https://j-hui.com/pages/yagg/):

## Acknowledgements
This was developed by Phillip Le, Leslie Chang, Xurxo Riesco, and Dorothy Zhang for COMS 3157 Spring '23

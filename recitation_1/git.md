# **Git for AP Workflow**

Git is a version control system designed for source code and other kinds of plain text. It is great for synchronizing work when you are working in a team, as well as keeping track of changes you make when you are working alone.

In this class, you are **required to use Git for your homework assignments.** You use it to obtain skeleton code, document your progress, and submit your work. You can also use Git to view my solutions, once I release them.

Git is first and foremost a command-line tool, invoked using the "git" command. "git" actually encompasses a number of subcommands, such as "git clone", "git pull", and "git checkout".
You can see the man pages for each subcommand using the --help flag:

	$ git clone --help  # brings up the man pages for git clone
	$ man git-clone     # does the same as above

Take this as a guide of **limited** use of Git and not **AP-specific** as these commands and workflow are used everywhere. Using Git is a great skill to build for those of you who plan on continuing to code at Columbia and beyond. 

# Understanding the Basics of Git


## What is a Git Commit?
Starting with the Git commit – the most integral part of using Git as a workflow manager. 

Commits are "snapshots" of your code throughout the various stages of development. Most git commands are oriented around updating and interacting with git commits, commands that we will go over below.

## Remote Repository and Skeleton Code
Now that we have established what Git and Git commits are, we can go ahead and start this demo! 

1. Check your email for an invitation on the **"cs3157-borowski-s23/hw#-team#"** repository and accept the invitation. 
2. Now, sign-in to GitHub.com, go to the top right profile icon and find 'Your Organizations'. You should see **"cs3157-borowski-s23"** listed as one of them, find the repository that corresponds with the assignment number that we are on (ie: hw1-team1)
3. This is **your remote repository** that you are working out of

You should see all the necessary skeleton code that we distribute for the assignment. Remember, this is your remote repository and now we need to create your **local repository** in order for you to actually work on the assignment. 

1. Click the green "<> Code" button, make sure you have selected 'SSH' and copy that link.
2. Open whatever interface you configured and go to the command-line and run `git clone <pasted-link>` 
3. If that was successful, you now have a **local repository**. 

Git has the concept of both a *local* and *remote* repository. When you ran `git clone`, it took contents of the git repository at the remote server hosted by github.com and copied it down to the local working environment. This means that you can navigate the files that were previously hosted only on GitHub as you would any other files. Throughout this recitation, we will do most work locally, and then *push* our changes from our local repository to the remote on GitHub.


## Repository Structure 
Git manages multiple copies of repo’s contents:

1. the working directory – where all your edits and created files will be (both in and out of your git repo)
2. the staging area (AKA "index") is what will form the next commit
3. each commit has a snapshot of your repo’s contents at some point in time

Git also keeps **HEAD**, which is a reference to your repo's most recent commit, aka staged **and** committed revision to your repo.

Thus, there are also multiple copies of each (tracked) file in your repo. Git will use these copies to automatically track changes between your working directory and last commit (IE: differences between the most committed version and files in the working directory)

**Note**: when you clone a repo, you will only receive its commit history; modifications in the working directory and staging area (files that are un-staged and non-committed) are not cloned.

## File States in Local Repository
In the your working directory, files can be in four different states:

1. **Untracked**: files that are not under Git revision control, a little deceiving.
2. **Tracked, unmodified**: the file is in the Git repository, and it has not been modified since the last commit.
3. **Tracked, modified, but unstaged**: this is a file that is under Git revision, you have made changes but have not staged these changes.
4. **Tracked, modified, and staged**: this is a file under Git revision, you made changes, and staged these changes.

## Piecing this all Together 

We just went over a lot of different terms but these are all necessary for understanding Git for AP workflow. Let's combine this understanding of repository structure and file states all together. 

1. Working Directory:

	I. **Untracked**: files that are not under Git revision control, these are files that were not part of skeleton code (ie: executables or files you created not included when you cloned remote repo)

	II. **Tracked, unmodified**: the file is in the Git repository, and it has not been modified since the last commit.

	III. **Tracked, modified, but unstaged**: this is a file that is under Git revision, you have made changes but have not staged these changes.

2. Staging Area: 

	I. **Tracked, modified, and staged**: this is a file under Git revision, you made changes, and staged these changes.

## Now in the Context of Your Assignment: 

1. The **HEAD** refers to the most recent revision, which is the last commit (the skeleton code if you just cloned). Git uses the HEAD as a reference for changes made to your local repository files.
2. As you code and make changes to the files, they are saved in the **working directory**. At this point, the HEAD (last commit) and the working directory differ.
3. To save the changes in the working directory and reflect them in the last commit, you need to stage them in the **staging area**.
4. Committing to the changes in the staging area updates the latest commit, making the **HEAD** refer to this latest commit.

You might be picking up this is a cycle, and that is because it is! You are editing and revising files and using that revision for the next edit and revision. 


# Working Responsibly in Git – Branching
**With or without a group**, there is definitely a *right* way to use Git that would maximize its many features that make Git a great workflow manager. Branching is **highly recommended** when completing the assignments (especially for those of you in a pair)

### Branching Overview

- Git branches allow you to create **multiple streams of development within the same repository**. Each branch has its own **HEAD**, which points to the latest commit in that branch. 

- When you create a new branch, it starts from the same place as the branch you created it from. You can then make separate commits to the new branch without affecting the original branch. 

- This makes it easy to isolate and manage different changes. When you're ready, you can merge the changes in your feature branch back into the original branch.

Make sure you are in your local repository and run `$git branch` it should say `* master` with the asterisk indicating that you are on the master branch. The master branch is the **default branch**, but Git also supports **main** as a default branch name as well.  

To make a new branch (don't be scared) run `git branch <insert-branch-name>`. Now run `git branch -a ` to see all the branches. 

Branches are made in your **local repository** and each branch is a copy of your local repository. To move to another branch and start coding on that branch, run `git checkout <insert-branch-name>`. You should see `Switched to branch '<insert-branch-name'>`. You can now start developing! 

### **Review: Git Commands for Branching** 
1. `$ git branch` shows the branch that you are currently working on in your local repo
2. `$ git branch -a` lists all the branches in your local repo 
3. `$ git branch <branch-name>` creates a branch named "<branch-name>" 
4. `$ git branch -b <branch-name>` in one step creates a branch named "<branch-name>" and checks out to it
5. `git checkout  <branch-name>` allows you to 'move' to the indicated branch 
6. `git push origin <branch-name>` pushes your local branch to your remote repo as well as all the commits you made on that branch 
	
# Let's Start Coding!  
Passed all the terminology we are going to get into the commands. We are going to go through the commands as they would need to be used as you are writing code. 

 1. You edit the skeleton file, as you would edit any file (eg. `vim <filename>`). These are edits that only exist in your working directory. 
 2. Run `git status`, this is a command that tells you the state of your working directory relative to last commit (**HEAD**). 
 3. If you want to check the difference between what you've committed and the changes you've made in the working directory, you'd run `git diff` to show these changes. 
 4. You are sure of these changes, and you want to commit them. Let's stage these files that are changed. Run `git add <file-name>` to stage these files for commit.
 5. Assure that all the changes to the files you want to commit are in the staging area, listed under the "Changes to be committed" when you run `git status`.
 6. You are ready to 'commit' to these changes! Run `git commit -m "<insert-short-message>"` Inside the quotations is your commit message, where you should summarize the changes you've made. You have made commit, this now becomes **HEAD** of this branch and is the latest revision of your local repository on **your branch**. This commit and all these changes will become the baseline of comparison that Git will use to recognize further changes. 
 7. Run `git log` to show your most recent commit as well as your commit history
 8. To push your committed changes from your local repository to the remote repository on GitHub, run `git push origin <branch-name>`. If you're not sure which branch you're working on, you can type `git branch` to check first. By pushing, you make your changes available to be seen by your teammate or anyone who has access to your remote repository on GitHub.

### Things to Remember:
1. Remember you committed these changes onto ***your specific branch***
2. Unlike `git add`, `git commit` status doesn't require you to specify specific files to commit, that is because `git commit` commits all the files that you staged
2. Try to make meaningful messages when you run `git commit` as they might be helpful for remembering what you did at each commit

 **Q:** After you commit but do not make changes to your file, is it possible to have unstaged and uncommitted changes in your working directory? 
 
 **A:** Yes, you commit only the changes in the files that you staged. However, whatever is unstaged still only exists in the working directory.  

## Branching, remember me? 
Of course you do! However, what we previously said about branching is that it is good to develop on separate branches and then create pull requests to propose merging those changes to the master branch. In cases where you want to add something that would not be jeopardizing to your code or if you are working with your partner in real time, there is a way to bypass branching off for edits completely. Proceed with caution, but this is how you can bypass creating separate branches for edits. 

	1. Checkout to the branch that you want to make edits on
	2. To get the latest version of that branch, run `~$ git pull` which will 'pull' the most recent commit of the remote repository (specific to the branch that you are on.) 
	3. Make your edits, stage them, commit them, and to push them onto the remote repository, run `~$git push origin <branch-name>` (this should be a familiar command. 

You and your partner can do this in a cycle, pushing and pulling each others commits to update the same branch. However, when making big changes or developing large chunks of code, we recommend going the branching route and creating a separate branch and opening a pull request. This is a lot safer and can prevent conflicts which we will go over in future sections. 
	
### **Review: Git Commands for Adding and Committing Changes** 
	
1. `$ git status` compares the last committed version of your repo and the working directory and indicates what stage each file is in
2. `$ git diff` Git will show you the exact differences between HEAD reference and working directory
3. `$ git add <filename(s)>` will stage files that have been modified, preparing them to be committed
4. `$ git commit -m "<short-message>` commits the tracked, modified, and staged files, updates HEAD reference, makes changes the most recent revision of git repo
5. `$ git log` will show your commit history 
6. `$ git push origin <branch-name>` pushes your local branch to your remote repo as well as all the commits you made on that branch
7. `$ git pull` gets the most recent commit from your remote repo and applies it to your local repo 

# Settling Differences Between Commits
Sounds dramatic, but really, Git is tracking a lot of differences between versions of your code. Let's take a look: 
1. Differences between files in your **working directory** the **staging area** and the last commit, **HEAD** 
2. Differences between branches in the your **local repository** 
2. Finally, differences between your **local** and **remote repository**

Let's begin to ***reconcile*** these differences step by step. Starting with #2 (since we went over #1 above). If you were following closely (which we really hope you are) this process is quite simple though you can resolve a lot of these differences. 

## Differences Between Two Local Branches

Creating two local branches can be beneficial for various reasons, say you want to preserve two separate branches that develop different parts of an assignment. That is one example, but whatever it may be, you might also want to **merge** two local branches.

1. Use `$ git checkout <branch-name` to move to the branch you want (could be either of the two you want to merge)
2. Use `$ git merge <branch-name>` to merge the two local branches. 
3. You will then use `$ git commit` to commit this merge, to which you can `~$git push` to push local branch to remote repo
	
## Differences Between a Local and Remote Branch

When working in a pair, you and/or your partner will be making updates to your master branch. Once you clone your remote repo, it only clones it the moment you run `~$ git clone` and does not update if your partner is updating any branch in your remote repo, including master. 
	
1. Using `$ git fetch` takes care of that discrepancy between local and remote repos, running this command will download the state of the remote repository and **put it into a branch named <remote>:<branch_name>**. This results in two branches: **local master branch** and **one with the most recent committed and pushed changes from GitHub**
	
2. If you want changes on GitHub to apply to your local branch, `$ git merge <branch-name>` will merge changes from the specified branch and the branch you are on. 
	
## Differences Between a Local Branch and Remote Repo
	
1. Since your branch is created from your local repository, you will need to 'upload' your branch to your remote repository. Run `git push origin <insert-branch-name>`
2. Now, go back to your remote repository (github.com) and refresh the page, you should see in a yellow-box 'Compare & pull request'.

Now, what is a pull request? 

## Pull Requests 
Pull requests are great for those of you that are working in pairs but even for those of you that are working alone they can be incredibly helpful. Pull requests allow you to propose the changes that you made on your own branch to be merged with another such as the master branch. 

If you clicked 'Compare & pull request', you should be prompted to create a title and leave a comment for your pull request. ***Everyone*** in your repository will see this. This pull request allows other members to see the changes you made on your branch (that you cloned from the master branch) and decide whether they want to **merge** these changes onto the **master branch**. 

In that "Pull request" you are able to look at the changes that your partner changed by clicking "Files changed". You are able to leave comments and questions to which you and your partner can decide to resolve. 

It is best practice that you run and test your code before you make your PR, as you can assure that your master branch is good-functioning code and your sub-branches are for developing. You and your partner can be working on different parts on the code on different branches, push your branches, and make pull requests to merge to the **master branch** which you will tag and the TA's will grade. 

If you (and your partner if applicable) decide to merge, you will make a merge commit, and your now merged (sub and master) will become the most recent revision of your code. 

Sounds simple, and sometimes it is! But there are times that you will run into **merge conflicts** when trying to merge a sub-branch and master branch. 

PR are a great tool, read more about them [here](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests). 

# Merge and Pull Conflicts

If you are working alone or working with a partner, merge conflicts are avoidable but ultimately inevitable (if you don't follow the directions above carefully). But they can be quite frightening. We talked about `$ git merge <branch-name>` above, but something we did not mention is that merge will automatically try to merge using a fast-forward approach which will succeed **if the changes you are merging do not conflict with one another** but will fail otherwise. 

Thus, we encourage that when merging two-local branches and a local branch to your remote repo, to run `$ git merge` with the `--no-ff` option like this: `$ git merge --no-ff <branch-name>`. 

Let's see an example of merge conflict. 


### Merge Conflict Example:

## Merge Conflict
A merge conflict may arise if: 
1. Changes to the same line(s) of code in two different branches.
2. Deletions of a file in one branch and changes to the same file in another branch.
3. If you have uncommitted changes in your branch and want to merge, this will overwrite your changes in working directory


### **What to do if you have a Merge Conflict?**
Let's trigger a merge conflict.
```bash
UNI@ap:~/cs3157/hw1-team0/src$ git branch -a 
* master 
  your-branch

UNI@ap:~/cs3157/hw1-team0/src$ git checkout your-branch
Switched to branch 'your-branch'
```
Up to this point we have seen that there are two branches. In both of those branches we have have a file named **AP.txt** that contains only one line Let's see what that looks like in each branch. Note `cat` is a bash command that when passed a file will output the files contents to the terminal (stdout to be precise). 

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
Then, of course, you would stage and commit the file –– this is what we call a **merge commit**. You can configure merge so that it will always merge with the `--no-ff option` option. To make this configuration apply to this repo, run `git config --add merge.ff false` add the --global flag to apply this configuration for **every** repo: `$ git config --global --add merge.ff false`.
	
## Pull Conflicts
Pull conflicts are sort of the same problem as a merge conflict. You might see this when running `$ git pull` you get, "You have divergent branches and need to specify how to reconcile them" along with a bunch of other scary messages. 

Remember from the previous section that `$ git pull` fetches any commits on your remote repo and merges them to your local repo. Like merge, there are two approaches that Git uses to merge the differences between your local and remote repo. 
	
**Scenario:**You cloned your remote repo and you decide to work on the master branch in your local repo. You make good progress and commit twice to your local repo (directly to your local master branch) but did not push to the remote repo. A day later, your partner also has done the same, but went ahead and pushed their changes onto the remote repo which includes three commits also directly on the master branch. 
	
Now, your branch is ahead 2 commits and simultaneously behind 3 commits from the remote master branch. You try to run `$ git pull but git tells you you have divergent branches. You need to configure pull so that it knows what to do in this situation. You have two options: 

### 1. Rebase: 
When you `$ git pull` with pull configured to rebase, all the commits in the remote repo (the committed and merged changes your parter made on the master branch) will get added to your local repo and ***your*** branch commits will be moved "ahead" of the master branch.  

### 2. Merging 
Using the same scenario, lets say you use the merge option. Both the steps that happened in rebase occur: the commits from the remote repo will get added to your local repo and your branch commits will be moved "on top" of the master branch but will actually merge the local remote changes and local branch and create a new merge commit. Since both branches will be preserved this is the safer option! 
	
### Rebase vs. Merging 

1. Commit History
Rebasing makes commit history linear, even when it is not. Using the scenario, remember that your friend made these changes after you and their commits are more recent. Yet, git pull with rebase configuration  ignores that and still places your local commits "ahead" of those that more recent commits that git copied from the remote repo. Merging will maintain commit history because of the way that it preserves the branches. 

2. Discrepancies Between Branches When Pulling
Another big difference, is that if there is discrepancies between branches when pulling, rebasing will let you handle them one commit at a time, while merging will have you handle them all at once. It is then easier to handle rebasing conflicts, but you might have to handle a lot more.

These are just a two reasons that may influence you to pull to rebase or merge, but it is up to you. You can also read more [here](https://www.atlassian.com/git/tutorials/merging-vs-rebasing)
	
### Configuring Pull 
We presented you the options and now you can make a decision on you wish to configure `$git pull`. Run these commands based on your decision:

1. Merge: run `$ git config pull.rebase false`
2. Rebase: `$ git config pull.rebase true`

You can use the --global option or edit your ~/.gitconfig file directly, to have that configuration apply to all repos. 
1. Merge: git config --global pull.rebase false
2. Rebase: git config --global pull.rebase true

## Other Git Resources

There are plenty of hands-on guides teaching you how to use Git.
Here are a few we recommend for getting started:

- man gittutorial: the official Git tutorial included in its man pages
- git - the simple guide (https://rogerdudler.github.io/git-guide/):

a guide that gets straight to the point with nice illustrations

- Yet Another Git Guide (https://j-hui.com/pages/yagg/):

## Acknowledgements
This was developed by Phillip Le, Leslie Chang, Xurxo Riesco, and Dorothy Zhang for COMS 3157 Spring '23

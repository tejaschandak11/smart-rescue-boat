# Git Setup Guide — Smart Rescue Boat

## Step-by-Step: Push Everything to GitHub

Run these commands **in order** in your terminal (Git Bash / CMD / Terminal).

---

### Step 1: Install Git (if not already installed)
Download from: https://git-scm.com/downloads

---

### Step 2: Configure Git with your identity (one-time setup)
```bash
git config --global user.name "Tejas Chandak"
git config --global user.email "tejaschandak3511@gmail.com"
```

---

### Step 3: Copy all the project files into a folder
Place all the downloaded files into a folder named `smart-rescue-boat` on your PC.

---

### Step 4: Open terminal in that folder, then run:

```bash
# Initialize git repo
git init

# Add your GitHub repo as remote
git remote add origin https://github.com/tejaschandak11/smart-rescue-boat.git

# Stage all files
git add .

# First commit
git commit -m "Initial commit: Full project structure with firmware stubs and documentation"

# Push to GitHub
git branch -M main
git push -u origin main
```

---

### Step 5: Verify
Visit https://github.com/tejaschandak11/smart-rescue-boat — you should see all files!

---

## Future Updates (when you add code)

```bash
git add .
git commit -m "Add: navigation obstacle avoidance implementation"
git push
```

## Good Commit Message Formats

- `Add: ultrasonic distance measurement in obstacle.c`
- `Fix: motor stall issue in Navigation_AvoidObstacle()`
- `Update: README with project photos`
- `Test: sensor unit test results added`

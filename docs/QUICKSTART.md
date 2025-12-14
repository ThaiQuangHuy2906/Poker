# Quick Start Guide - Push to GitHub

## 🚀 5 Phút để đưa project lên GitHub

### Bước 1: Kiểm tra files (30 giây)
```bash
cd "e:\Personal Project\Poker"
dir
```
Đảm bảo có các file chính:
- ✅ main.cpp
- ✅ Utils.h/cpp
- ✅ TexasHoldemPoker.h/cpp
- ✅ README.md
- ✅ .gitignore
- ✅ LICENSE

### Bước 2: Build để test (1 phút)
```bash
.\build.bat
```
Hoặc:
```bash
g++ -std=c++11 main.cpp Utils.cpp TexasHoldemPoker.cpp TwoFiveHihi.cpp SurprisingSwap.cpp -o Poker.exe
```

### Bước 3: Test game (1 phút)
```bash
.\Poker.exe
```
Chọn game 1 (Texas Hold'em) và test một vài vòng chơi.

### Bước 4: Initialize Git (1 phút)
```bash
# Khởi tạo git repository
git init

# Thêm tất cả files
git add .

# Commit lần đầu
git commit -m "Initial commit: Poker game collection with modular structure"
```

### Bước 5: Tạo GitHub Repository (1 phút)
1. Mở https://github.com/new
2. Repository name: `Poker` hoặc `PokerGameCollection`
3. Description: `A collection of poker game variants in C++ (Texas Hold'em, Two Five Hihi, Surprising Swap)`
4. Public/Private: Chọn theo ý bạn
5. **KHÔNG tick** "Add a README file" (đã có sẵn)
6. **KHÔNG tick** "Add .gitignore" (đã có sẵn)
7. Click "Create repository"

### Bước 6: Push lên GitHub (1 phút)
```bash
# Thêm remote repository (thay YOUR_USERNAME và REPO_NAME)
git remote add origin https://github.com/YOUR_USERNAME/REPO_NAME.git

# Đổi branch sang main
git branch -M main

# Push code lên GitHub
git push -u origin main
```

## ✅ Xong! Project đã trên GitHub!

## Xem kết quả:
Mở: `https://github.com/YOUR_USERNAME/REPO_NAME`

Bạn sẽ thấy:
- ✅ README.md hiển thị đẹp với đầy đủ thông tin
- ✅ Code được tổ chức gọn gàng
- ✅ License, Contributing, Build instructions
- ✅ Commit history

## Lưu ý quan trọng:

### ⚠️ Nếu gặp lỗi authentication:
GitHub không còn hỗ trợ password. Bạn cần:

**Option 1: Personal Access Token (Recommended)**
1. GitHub → Settings → Developer settings → Personal access tokens → Tokens (classic)
2. Generate new token (classic)
3. Chọn `repo` scope
4. Copy token
5. Khi push, paste token thay vì password

**Option 2: GitHub CLI**
```bash
# Cài đặt GitHub CLI
winget install GitHub.cli

# Login
gh auth login

# Push
gh repo create REPO_NAME --public --source=. --push
```

**Option 3: SSH Key**
```bash
# Tạo SSH key
ssh-keygen -t ed25519 -C "your_email@example.com"

# Add to GitHub
# Copy ~/.ssh/id_ed25519.pub
# GitHub → Settings → SSH keys → New SSH key

# Thay đổi remote URL
git remote set-url origin git@github.com:YOUR_USERNAME/REPO_NAME.git
```

## Các lệnh Git hữu ích khác:

```bash
# Xem status
git status

# Xem remote
git remote -v

# Add thêm files
git add .
git commit -m "Update something"
git push

# Xem history
git log --oneline

# Tạo branch mới
git checkout -b feature-name
```

## Sau khi push thành công:

### 1. Thêm Topics/Tags trên GitHub:
- `cpp`
- `poker`
- `texas-holdem`
- `game`
- `console-game`
- `windows`

### 2. Cập nhật README nếu cần:
```bash
# Edit README.md
git add README.md
git commit -m "Update README"
git push
```

### 3. Tạo Release (Optional):
1. GitHub → Releases → Create a new release
2. Tag: `v1.0.0`
3. Title: `Initial Release`
4. Description: Copy từ CHANGELOG.md
5. Attach Poker.exe (optional)

## Next Steps (Tùy chọn):

### A. Add CI/CD:
Tạo `.github/workflows/build.yml` để tự động build khi push code

### C. Add Screenshots:
1. Tạo folder `screenshots/`
2. Chụp ảnh game
3. Add vào README.md

### D. Add Wiki:
GitHub → Wiki → Create first page với detailed game rules

## Troubleshooting:

### "git: command not found"
```bash
# Cài Git
winget install Git.Git
```

### "Permission denied"
Xem phần authentication ở trên

### "Repository not found"
Kiểm tra URL: `git remote -v`

### Muốn đổi tên repository:
GitHub → Settings → Repository name

## 🎉 Congratulations!

Project của bạn đã sẵn sàng để:
- ✅ Share với bạn bè
- ✅ Add vào CV/Portfolio
- ✅ Contribute từ community
- ✅ Learn Git/GitHub

---

**Need help?** Check:
- BUILD.md - Build instructions
- README.md - Project overview
- CONTRIBUTING.md - How to contribute

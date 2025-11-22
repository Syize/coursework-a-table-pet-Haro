# This is an example PKGBUILD file. Use this as a start to creating your own,
# and remove these comments. For more information, see 'man PKGBUILD'.
# NOTE: Please fill out the license field for your package! If it is unknown,
# then please put 'unknown'.

# Maintainer: Your Name <youremail@domain.com>
pkgname=haro-pet
pkgver=1.0.0
pkgrel=1
epoch=0
pkgdesc="Haro, a desktop pet"
arch=('x86_64')
url="https://github.com/Syize/coursework-a-table-pet-Haro"
license=('MIT')
groups=()
depends=('qt5-base >= 5.15', 'qt5-multimedia >= 5.15', 'qt5-translations >= 5.15', 'gst-plugins-base')
makedepends=('clang', 'llvm-libs', 'gcc', 'compiler-rt', 'cmake', 'ninja')
checkdepends=()
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=()
install=
changelog=
source=("$pkgname-$pkgver.tar.gz"
        "$pkgname-$pkgver.patch")
noextract=()
md5sums=()
validpgpkeys=()

prepare() {
	cd "$pkgname-$pkgver"
	patch -p1 -i "$srcdir/$pkgname-$pkgver.patch"
}

build() {
	cd "$pkgname-$pkgver"
	./configure --prefix=/usr
	make
}

check() {
	cd "$pkgname-$pkgver"
	make -k check
}

package() {
	cd "$pkgname-$pkgver"
	make DESTDIR="$pkgdir/" install
}

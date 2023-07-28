//Daniel Asensi Roch
//Compilación g++ -o tribu Tribu.c -lpthread

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Olla {
 private:
  int misioneros;
  std::mutex m;
  std::condition_variable olla_llena;
  std::condition_variable olla_vacia;

 public:
  Olla(int misioneros) : misioneros(misioneros) {}

  void SirveMisionero() {
    std::unique_lock<std::mutex> lock(m);
    olla_llena.wait(lock, [this]() { return misioneros > 0; });
    misioneros--;
    std::cout << "Un miembro de la tribu se ha servido de la olla. Quedan " << misioneros << " misioneros." << std::endl;
    if (misioneros == 0) {
      olla_vacia.notify_one();
    }
  }

  void LlenarOlla() {
    std::unique_lock<std::mutex> lock(m);
    olla_vacia.wait(lock, [this]() { return misioneros == 0; });
    misioneros = 10;
    std::cout << "El cocinero ha llenado la olla con 10 misioneros." << std::endl;
    olla_llena.notify_all();
  }
};

int main() {
  Olla olla(10);

  std::thread cocinero( [&olla]() {
    while (true) {
      olla.LlenarOlla();
    }
  });

  std::thread miembro1( [&olla]() {
    while (true) {
      olla.SirveMisionero();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  });

  std::thread miembro2( [&olla]() {
    while (true) {
      olla.SirveMisionero();
      std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
  });
  cocinero.join();
  miembro1.join();
  miembro2.join();
  return 0;
}
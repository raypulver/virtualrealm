#include "virtualrealm.h"

int main(int argc, char **argv) {
  VirtualRealm::Ptr vr = VirtualRealm::Init(50000);
  vr->Run();
  return 0;
}

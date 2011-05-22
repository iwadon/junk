#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <cstddef>
#include <iostream>
#if defined(HAVE_PCAP_PCAP_H)
#include <pcap/pcap.h>
#elif defined(HAVE_PCAP_H)
#include <pcap.h>
#endif

#define PCAP_ERROR_(func) std::cerr << #func << "() failed: " << errbuf << std::endl

int main()
{
  char errbuf[PCAP_ERRBUF_SIZE];
  static const size_t PACKET_BUFSIZ = 256;

  char *dev = pcap_lookupdev(errbuf);
  if (dev == NULL) {
    PCAP_ERROR_(pcap_lookupdev);
    return 1;
  }
  std::cout << "device: " << dev << std::endl;

  pcap_t *handle = pcap_open_live(dev, PACKET_BUFSIZ, 1, 1000, errbuf);
  if (handle == NULL) {
    PCAP_ERROR_(pcap_open_live);
    return 1;
  }

  bpf_program prog;
  static const char filter_src[] = "port 53";
  static const bpf_u_int32 netmask = 0xffffff00;
  int ret = pcap_compile(handle, &prog, filter_src, 0, netmask);
  if (ret == -1) {
    PCAP_ERROR_(pcap_compile);
    pcap_close(handle);
    return 1;
  }

  ret = pcap_setfilter(handle, &prog);
  if (ret == -1) {
    PCAP_ERROR_(pcap_setfilter);
    pcap_close(handle);
    return 1;
  }

  pcap_pkthdr pkthdr;
  const unsigned char *packet = pcap_next(handle, &pkthdr);
  if (packet == NULL) {
    PCAP_ERROR_(pcap_next);
    pcap_close(handle);
    return 1;
  }
  std::cout << "pkthdr.len=" << pkthdr.len << std::endl;

  pcap_close(handle);
  return 0;
}

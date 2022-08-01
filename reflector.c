#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <bpf/bpf_helpers.h>

SEC("xdp")
/* Reflect ethernet frames back to the sender */
int xdp_reflector(struct xdp_md *ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    struct ethhdr *eth = data;

    if (data + sizeof(*eth) > data_end)
        return XDP_DROP;

    #pragma unroll
    for (int i = 0; i < 6; ++i) {
        char tmp = eth->h_source[i];
        eth->h_source[i] = eth->h_dest[i];
        eth->h_dest[i] = tmp;
    }

    return XDP_TX;
}

char _license[] SEC("license") = "MIT";

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

    __u8 h_tmp[ETH_ALEN];
    __builtin_memcpy(h_tmp, eth->h_dest, ETH_ALEN);
    __builtin_memcpy(eth->h_dest, eth->h_source, ETH_ALEN);
    __builtin_memcpy(eth->h_source, h_tmp, ETH_ALEN);

    return XDP_TX;
}

char _license[] SEC("license") = "MIT";

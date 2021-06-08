 #include <linux/clk.h>
 #include <linux/err.h>
 #include <linux/interrupt.h>
 #include <linux/kernel.h>
 #include <linux/mfd/syscon.h>
 #include <linux/module.h>
 #include <linux/of_address.h>
 #include <linux/of_device.h>
 #include <linux/platform_device.h>
 #include <linux/regmap.h>
 #include <linux/remoteproc.h>

struct st_rproc_config {
	bool                    sw_reset;
	bool                    pwr_reset;
	unsigned long           bootaddr_mask;
};

struct rtt_rproc {
	struct rtt_rproc_config  *config;
};

static const struct of_device_id rtt_rproc_match[] = {
	{ .compatible = "rtt,dummy-rproc" },
	{},
};

static int rtt_rproc_start(struct rproc *rproc) {
	pr_err("rtt_rproc_start\n");
	return 0;
}

static int rtt_rproc_stop(struct rproc *rproc) {
	pr_err("rtt_rproc_stop\n");
	return 0;
}

#if 0
static int rtt_rproc_parse_fw(struct rproc *rproc) {
	pr_err("rtt_parse_fw\n");
	return 0;
}

static int rproc_elf_load_segments(struct rproc *rproc) {
	pr_err("rproc_elf_load_segments\n");
	return 0;
}

static int rproc_elf_find_loaded_rsc_table(struct rproc *rproc) {
	pr_err("rproc_elf_find_loaded_rsc_table\n");
	return 0;
}

static int rproc_elf_sanity_check(struct rproc *rproc) {
	pr_err("rproc_elf_sanity_check\n");
	return 0;
}

static int rproc_elf_get_boot_addr(struct rproc *rproc) {
	pr_err("rproc_elf_get_boot_addr");
	return 0;
}
#endif

static const struct rproc_ops rtt_rproc_ops = {
	.start                  = rtt_rproc_start,
	.stop                   = rtt_rproc_stop,
#if 0
	.parse_fw               = rtt_rproc_parse_fw,
	.load                   = rproc_elf_load_segments,
	.find_loaded_rsc_table  = rproc_elf_find_loaded_rsc_table,
	.sanity_check           = rproc_elf_sanity_check,
	.get_boot_addr          = rproc_elf_get_boot_addr,
#endif
};

static int rtt_rproc_probe(struct platform_device *pdev) {
	struct device *dev = &pdev->dev;
	const struct of_device_id *match;
	struct rproc *rproc;
	struct rtt_rproc *ddata;
	int ret;

	pr_err("start probe\n");
	match = of_match_device(rtt_rproc_match, dev);
	if (!match) {
		dev_err(dev, "This is not rtt dummy remoteproc\n");
		return -ENODEV;
	}

	rproc = rproc_alloc(dev, "rtt-rproc", &rtt_rproc_ops, NULL, sizeof(*ddata));
	if(!rproc) {
		dev_err(dev, "Allocate Failed!\n");
		return -ENOMEM;
       	}
	rproc->has_iommu = false;
	ddata = rproc->priv;

	ret = rproc_add(rproc);
	if(ret) {
		dev_err(dev, "Remoteproc add failed\n");
		return ret;
	}

	return 0;
}

static int rtt_rproc_remove(struct platform_device *pdev) {
	return 0;
}

static struct platform_driver rtt_rproc_driver = {
	.probe = rtt_rproc_probe,
	.remove = rtt_rproc_remove,
	.driver = {
		.name = "rtt-rproc",
		.of_match_table = of_match_ptr(rtt_rproc_match),
	},
};
module_platform_driver(rtt_rproc_driver);

MODULE_DESCRIPTION("RT-Thread Remote Processor Control Driver");
MODULE_AUTHOR("Bo Dong <bdong@ucrobotics.com>");
MODULE_LICENSE("GPL v2");

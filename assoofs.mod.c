#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_MITIGATION_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const char ____versions[]
__used __section("__versions") =
	"\x1c\x00\x00\x00\x48\x9f\xdb\x88"
	"__check_object_size\0"
	"\x18\x00\x00\x00\xc2\x9c\xc4\x13"
	"_copy_from_user\0"
	"\x1c\x00\x00\x00\x87\xe9\x64\xbc"
	"register_filesystem\0"
	"\x14\x00\x00\x00\x47\x29\x92\x6b"
	"mount_bdev\0\0"
	"\x20\x00\x00\x00\xf0\x65\xe4\xb6"
	"unregister_filesystem\0\0\0"
	"\x1c\x00\x00\x00\x34\xdb\x8c\x53"
	"mark_buffer_dirty\0\0\0"
	"\x1c\x00\x00\x00\x71\x9f\xc5\x17"
	"sync_dirty_buffer\0\0\0"
	"\x14\x00\x00\x00\x7c\x6d\xe7\x76"
	"new_inode\0\0\0"
	"\x18\x00\x00\x00\xcf\x5b\xfc\xba"
	"current_time\0\0\0\0"
	"\x1c\x00\x00\x00\x63\xa5\x03\x4c"
	"random_kmalloc_seed\0"
	"\x18\x00\x00\x00\x1d\x07\x60\x20"
	"kmalloc_caches\0\0"
	"\x20\x00\x00\x00\xee\xfb\xb4\x10"
	"__kmalloc_cache_noprof\0\0"
	"\x18\x00\x00\x00\x56\x41\x31\xbc"
	"nop_mnt_idmap\0\0\0"
	"\x1c\x00\x00\x00\x70\xf5\xd5\x1f"
	"inode_init_owner\0\0\0\0"
	"\x10\x00\x00\x00\x5a\x25\xd5\xe2"
	"strcmp\0\0"
	"\x2c\x00\x00\x00\x61\xe5\x48\xa6"
	"__ubsan_handle_shift_out_of_bounds\0\0"
	"\x10\x00\x00\x00\x4b\x1d\x00\x89"
	"d_add\0\0\0"
	"\x10\x00\x00\x00\x9c\x53\x4d\x75"
	"strlen\0\0"
	"\x10\x00\x00\x00\x38\xdf\xac\x69"
	"memcpy\0\0"
	"\x18\x00\x00\x00\xb5\x79\xca\x75"
	"__fortify_panic\0"
	"\x14\x00\x00\x00\x26\x3e\x1c\xe1"
	"d_make_root\0"
	"\x20\x00\x00\x00\x85\xe2\xdd\x88"
	"generic_delete_inode\0\0\0\0"
	"\x1c\x00\x00\x00\x7e\x15\x08\x03"
	"kill_block_super\0\0\0\0"
	"\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
	"__fentry__\0\0"
	"\x14\x00\x00\x00\xef\xb6\xb3\x4c"
	"__bread_gfp\0"
	"\x24\x00\x00\x00\x97\x70\x48\x65"
	"__x86_indirect_thunk_rax\0\0\0\0"
	"\x14\x00\x00\x00\x6b\x11\x22\x18"
	"__brelse\0\0\0\0"
	"\x1c\x00\x00\x00\xca\x39\x82\x5b"
	"__x86_return_thunk\0\0"
	"\x10\x00\x00\x00\x7e\x3a\x2c\x12"
	"_printk\0"
	"\x18\x00\x00\x00\xde\x9f\x8a\x25"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "D48543EDDD647C533558AC3");

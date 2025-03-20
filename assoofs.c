#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO  */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/fs.h>           /* libfs stuff           */
#include <linux/buffer_head.h>  /* buffer_head           */
#include <linux/slab.h>         /* kmem_cache            */
#include "assoofs.h"

MODULE_LICENSE("GPL");

/*
 *  Prototipos de funciones
 */
static struct dentry *assoofs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data);
int assoofs_fill_super(struct super_block *sb, void *data, int silent);
ssize_t assoofs_read(struct file * filp, char __user * buf, size_t len, loff_t * ppos);
ssize_t assoofs_write(struct file * filp, const char __user * buf, size_t len, loff_t * ppos);
static int assoofs_iterate(struct file *filp, struct dir_context *ctx);
static int assoofs_create(struct mnt_idmap *idmap, struct inode *dir, struct dentry *dentry, umode_t mode, bool excl); //MODIFICADO MIGRACION el primer argumento
struct dentry *assoofs_lookup(struct inode *parent_inode, struct dentry *child_dentry, unsigned int flags);
static int assoofs_mkdir(struct mnt_idmap *idmap, struct inode *dir , struct dentry *dentry, umode_t mode); //MODIFICADO MIGRACION el primer argumento cambia
static int assoofs_remove(struct inode *dir, struct dentry *dentry);

/*
 *  Estructuras de datos necesarias
 */

// Definicion del tipo de sistema de archivos assoofs
static struct file_system_type assoofs_type = {
    .owner   = THIS_MODULE,
    .name    = "assoofs",
    .mount   = assoofs_mount,
    .kill_sb = kill_block_super,
};

// Operaciones sobre ficheros
const struct file_operations assoofs_file_operations = {
    .read = assoofs_read,
    .write = assoofs_write,
};

// Operaciones sobre dircctorios
const struct file_operations assoofs_dir_operations = {
    .owner = THIS_MODULE,
    .iterate_shared = assoofs_iterate, //MODIFICADO MIGRACION
};
// Operaciones sobre inodos
static struct inode_operations assoofs_inode_ops = {
    .create = assoofs_create,
    .lookup = assoofs_lookup,
    .mkdir = assoofs_mkdir,
    .unlink = assoofs_remove,
    .rmdir = assoofs_remove,
};
// Operaciones sobre el superbloque
static const struct super_operations assoofs_sops = {
    .drop_inode = generic_delete_inode,
};


/*
 *  Funciones que realizan operaciones sobre ficheros
 */

ssize_t assoofs_read(struct file * filp, char __user * buf, size_t len, loff_t * ppos) {
    printk(KERN_INFO "Read request\n");
    return 0;
}

ssize_t assoofs_write(struct file * filp, const char __user * buf, size_t len, loff_t * ppos) {
    printk(KERN_INFO "Write request\n");
    return 0;
}

/*
 *  Funciones que realizan operaciones sobre directorios
 */

static int assoofs_iterate(struct file *filp, struct dir_context *ctx) {
    printk(KERN_INFO "Iterate request\n");
    return 0;
}

/*
 *  Funciones que realizan operaciones sobre inodos
 */
struct dentry *assoofs_lookup(struct inode *parent_inode, struct dentry *child_dentry, unsigned int flags) {
    printk(KERN_INFO "Lookup request\n");
    return NULL;
}


static int assoofs_create(struct mnt_idmap *idmap, struct inode *dir, struct dentry *dentry, umode_t mode, bool excl) {
    printk(KERN_INFO "New file request\n");
    return 0;
}

static int assoofs_mkdir(struct mnt_idmap *idmap, struct inode *dir , struct dentry *dentry, umode_t mode) {
    printk(KERN_INFO "New directory request\n");
    return 0;
}

static int assoofs_remove(struct inode *dir, struct dentry *dentry){
    printk(KERN_INFO "assoofs_remove request\n");
    return 0;
}

/*
 *  Inicialización del superbloque
 */
int assoofs_fill_super(struct super_block *sb, void *data, int silent) {   
    printk(KERN_INFO "assoofs_fill_super request\n");
    // 1.- Leer la información persistente del superbloque del dispositivo de bloques  
    struct buffer_head *bh;//estructura que represeta un bloque en el disco con todos sus parametros en el kernel
    struct assoofs_super_block_info *assoofs_sb;//estructura que sirve para representar la informacion del superbloque
    bh = sb_bread(sb, ASSOOFS_SUPERBLOCK_BLOCK_NUMBER);//cargamos el superbloque en bh
    // 2.- Comprobar los parámetros del superbloque
    assoofs_sb = (struct assoofs_super_block_info *)bh->b_data;//cargamos los datos del bloque en la estructura assoofs_sb
    if(assofs_sb->magic != ASSOOFS_MAGIC){//comprobamos que el magic number sea el correcto
        printk("Error al comprobar el numero magico del superbloque\n");
        return -1;
    }
    if(assoofs_sb->block_size != ASSOOFS_DEFAULT_BLOCK_SIZE){//comprobamos que el tamaño del bloque sea el correcto
        printk("Error al comprobar el tamaño de bloque del superbloque\n");
        return -1;
    }
    // 3.- Escribir la información persistente leída del dispositivo de bloques en el superbloque sb, incluído el campo s_op con las operaciones que soporta.
    sb->s_magic = ASSOOFS_MAGIC;//asignamos el magic number al superbloque en el kernel
    sb->s_maxbytes = ASSOOFS_DEFAULT_BLOCK_SIZE;//asignamos el tamaño maximo de bytes al superbloque en el kernel
    sb->s_op = assoofs_sops;//Puede ser que aqui me falte un & pero no estoy seguro
    sb->s_fs_info = assoofs_sb;//asignamos la informacion del superbloque a la informacion del superbloque en el kernel
    // 4.- Crear el inodo raíz y asignarle operaciones sobre inodos (i_op) y sobre directorios (i_fop)
    struct inode *root_inode;//creamos un inodo para el directorio raiz
    root_inode = new_inode(sb);//creamos un nuevo inodo
    inode_init_owner(&nop_mnt_idmap,root_inode,NULL,S_IFDIR);//inicializamos el inodo asignandole un directorio padre nulo y con la flag de los directorios
    root_inode->i_ino = ASSOOFS_ROOTDIR_INODE_NUMBER;//asignamos el numero de inodo al inodo raiz
    root_inode->i_sb = sb;//asignamos el puntero al superbloque raiz
    root_inode->i_op = &assoofs_inode_ops;//asignamos las operaciones sobre inodos al inodo raiz
    root_inode->i_fop = &assoofs_dir_operations;//asignamos las operaciones sobre directorios al inodo raiz
    struct timespec64 ts = current_time(root_inode);//creamos una estructura de tiempo para asignarla al inodo raiz
    inode_set_ctime(root_inode,ts.tv_sec,ts.tv_nsec);//asignamos la hora de creacion al inodo raiz
    inode_set_mtime(root_inode,ts.tv_sec,ts.tv_nsec);//asignamos la hora de modificacion al inodo raiz
    inode_set_atime(root_inode,ts.tv_sec,ts.tv_nsec);//asignamos la hora de acceso al inodo raiz
    root_inode->i_private = assoofs_get_inode_info(sb,ASSOOFS_ROOTDIR_INODE_NUMBER);//asignamos la informacion del inodo raiz
    sb->s_root = d_make_root(root_inode);//asignamos el inodo raiz al superbloque
    return 0;
}

/*
 *  Montaje de dispositivos assoofs
 */
static struct dentry *assoofs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data) {
    struct dentry *ret;
    printk(KERN_INFO "assoofs_mount request\n");
    ret = mount_bdev(fs_type, flags, dev_name, data, assoofs_fill_super);
    // Control de errores a partir del valor de retorno. En este caso se puede utilizar la macro IS_ERR: if (IS_ERR(ret)) ...
    return ret;
}



static int __init assoofs_init(void) {
    int ret;
    printk(KERN_INFO "assoofs_init request\n");
    ret = register_filesystem(&assoofs_type);
    // Control de errores a partir del valor de retorno
    return ret;
}

static void __exit assoofs_exit(void) {
    int ret;
    printk(KERN_INFO "assoofs_exit request\n");
    ret = unregister_filesystem(&assoofs_type);
    // Control de errores a partir del valor de retorno
}

module_init(assoofs_init);
module_exit(assoofs_exit);

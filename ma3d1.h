/* Mario Artist Polygon Studio structs */

/* MA3D1 / GSBLK / GSEXP main header (starting at 0x480) */
/* Info taken from Polygon Studio debug info */
struct ma3d1_hdr {
	u32 num_models;		/* 0x00 */
	u32 num_vtx;		/* 0x04 */
	u32 num_triangles;	/* 0x08 */
	u32 data_start;		/* 0x0C */
	u32 data_size;		/* 0x10 */
	u32 tex_start;		/* 0x14 */
	u32 tex_size;		/* 0x18 */
	u32 craft_mode;		/* 0x1C */
	u32 model_counter;	/* 0x20 */
	u32 num_group;		/* 0x24 */
	u32 num_block;		/* 0x28 */
	u32 group_start;	/* 0x2C */
	u32 group_size;		/* 0x30 */
	u32 block_start;	/* 0x34 */
	u32 block_size;		/* 0x38 */
	u32 geo_base;		/* 0x3C */
	u32 geo_env;		/* 0x40 */
	u32 geo_light;		/* 0x44 */
	u32 geo_anim;		/* 0x48 */
	u32 geo_back;		/* 0x4C */
	u32 back_start;		/* 0x50 */
	u32 back_size;		/* 0x54 */
	float[16] trans;	/* 0x58 */
	float[16] rot;		/* 0x98 */
	float[16] scale;	/* 0xD8 */
	u32 auto_class;		/* 0x118 */
	u32 auto_app;		/* 0x11C */
	u32 auto_mode;		/* 0x120 */
};

/* These are guessed */

/* Model Data */
struct data_hdr {
	u32 num_vertdefs;	/* 0x00 */
	u32 num_unkdefs;	/* 0x04 */
	u32 num_tridefs;	/* 0x08 */
	u32 unk1;		/* 0x0C */
	
	u32 vertdefs_start;	/* 0x10 */
	u32 vertdefs_size;	/* 0x14 */
	u32 unkdefs_start;	/* 0x18 */
	u32 unkdefs_size;	/* 0x1C */
	u32 tridefs_start;	/* 0x20 */
	u32 tridefs_size;	/* 0x24 */
	u32 tex_offset;		/* 0x28 */
	u32 tex_size;		/* 0x2C */
	
	u32 data_entry_size;	/* 0x30 */
	u32 unk2;		/* 0x34 */
}

struct vertdef {
	s16 px;
	s16 py;
	s16 pz;
	s8 nx;
	s8 ny;
	s8 nz;
	u8 unk;
}

struct unkdef {
	u8 unk[22];
}

struct tridef {
	u16 v1;
	u16 v2;
	u16 v3;
	u16 unk1;
	u16 unk2;
	u16 unk3;
	u16 unk4;
}

/* Block Data */
/* Contains array of blockdefs, amount = num_block */
struct blockdef {
	u32 id;
	u32 unk1;
	u32 unk2;
	u32 unk3;
	u32 rgba;
	float[16] trans;
	float[16] rot;
	float[16] scale;
}

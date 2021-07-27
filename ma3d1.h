/* Mario Artist Polygon Studio structs */
/* Huge thanks to jrra and krom */

/* MA3D1 / GSBLK / GSEXP main header (starting at 0x480, after 24x24 RGBA16 Thumbnail Image) */
/* Info taken from Polygon Studio debug info */
struct ma3d1_hdr {	/* 0x200 bytes */
	u32 num_models;		/* 0x00 */ /* Number of Models */
	u32 num_vtx;		/* 0x04 */ /* Number of Vertices */
	u32 num_triangles;	/* 0x08 */ /* Number of Triangles */
	u32 data_start;		/* 0x0C */ /* Models: To array of modeldefs */
	u32 data_size;		/* 0x10 */ /* Models: Byte size of array */
	u32 tex_start;		/* 0x14 */ /* Models: To Texture Data */
	u32 tex_size;		/* 0x18 */ /* Models: Byte size of Texture Data */
	u32 craft_mode;		/* 0x1C */ /* 0 = Disabled, 1 = Enabled */
	u32 model_counter;	/* 0x20 */
	u32 num_group;		/* 0x24 */ /* Number of Groups */
	u32 num_block;		/* 0x28 */ /* Number of Blocks */
	u32 group_start;	/* 0x2C */ /* Group: ? */
	u32 group_size;		/* 0x30 */ /* Group: ? */
	u32 block_start;	/* 0x34 */ /* Block: To array of blockdefs */
	u32 block_size;		/* 0x38 */ /* Block: Byte size of array */
	u32 geo_base;		/* 0x3C */ /* Stage: ? */
	u32 geo_env;		/* 0x40 */ /* Stage: Stage ID */
	u32 geo_light;		/* 0x44 */ /* Stage: Lighting ID */
	u32 geo_anim;		/* 0x48 */ /* Stage: Effect ID */
	u32 geo_back;		/* 0x4C */ /* Stage: Background Image ID */
	u32 back_start;		/* 0x50 */ /* Stage: Unused feature, custom background image */
	u32 back_size;		/* 0x54 */
	float[16] trans;	/* 0x58 */ /* Stage: 4x4 Matrix - Main Block Transform */
	float[16] rot;		/* 0x98 */ /* Stage: 4x4 Matrix - Main Block Rotation */
	float[16] scale;	/* 0xD8 */ /* Stage: 4x4 Matrix - Main Block Scale */
	u32 auto_class;		/* 0x118 */
	u32 auto_app;		/* 0x11C */
	u32 auto_mode;		/* 0x120 */
	u32 unk;		/* 0x124 */ /* Always 0xF000A3D1? */
};

/* These are guessed */

/* Model Data */
struct modeldef {
	u32 num_vertdefs;	/* 0x00 */
	u32 num_facedefs;	/* 0x04 */
	u32 num_tridefs;	/* 0x08 */
	u32 shade;		/* 0x0C */ /* 0 = Flat, 1 = Smooth */
	
	u32 vertdefs_start;	/* 0x10 */ /* from current modeldef */
	u32 vertdefs_size;	/* 0x14 */
	u32 facedefs_start;	/* 0x18 */ /* from current modeldef */
	u32 facedefs_size;	/* 0x1C */
	u32 tridefs_start;	/* 0x20 */ /* from current modeldef */
	u32 tridefs_size;	/* 0x24 */
	u32 tex_offset;		/* 0x28 */ /* from start of texture data */
	u32 tex_size;		/* 0x2C */
	
	u32 data_entry_size;	/* 0x30 */ /* byte size, includes modeldef, vertdefs, facedefs, and tridefs */
	u32 num_edges;		/* 0x34 */

	/* includes vertdefs, facedefs, tridefs */
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

struct facedef {
	u16 unk[17];
}

struct tridef {
	u16 v1;
	u16 v2;
	u16 v3;
	u16 unk1;
	u16 unk2;
	u16 tri_idx;
	u16 face_idx;
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

/* Texture Data */
/* 32x32 RGBA16 Images, for 2 triangles each, 2048 bytes each */

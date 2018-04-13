//MA3D1 to OBJ Converter

#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t getBE32(FILE *in)
{
	unsigned char bytes[4] = { 0, 0, 0, 0 };
	int test = 0;

	for (int i = 3; i >= 0; i--)
	{
		test = fgetc(in);
		if (test != EOF)
		{
			#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			bytes[i] = (unsigned char)test;
			#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			bytes[3 - i] = (unsigned char)test;
			#else
			bytes[i ^ 1] = (unsigned char)test;
			#endif
		}
	}
	return *((uint32_t*)&bytes[0]);
}

short getBE16(FILE *in)
{
	unsigned char bytes[2] = { 0, 0 };
	int test = 0;

	for (int i = 1; i >= 0; i--)
	{
		test = fgetc(in);
		if (test != EOF)
		{
			#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			bytes[i] = (unsigned char)test;
			#else
			bytes[i ^ 1] = (unsigned char)test;
			#endif
		}
	}
	return *((short*)&bytes[0]);
}

char get8(FILE *in)
{
	unsigned char bytes = 0;
	int test = fgetc(in);
	if (test != EOF)
	{
		bytes = (unsigned char)test;
	}
	
	return *((char*)&bytes);
}

uint32_t	numModels;
uint32_t	numVerts;
uint32_t	numTris;
uint32_t	modelOffset;
uint32_t	modelSize;

uint32_t	curModelOffset;
uint32_t	curVerts;
uint32_t	curTris;

struct vertDef {
	short px, py, pz;
	char nx, ny, nz;
	char unk;
};

struct triDef {
	short v1, v2, v3;
	uint32_t unk1, unk2;
};

struct modeldata {
	uint32_t numVerts;
	uint32_t numTris;

	uint32_t vertDefOffset;
	uint32_t vertDefSize;

	uint32_t triDefOffset;
	uint32_t triDefSize;

	uint32_t modelNextOffset;

	//add
	uint32_t vertDefFirst;
	uint32_t triDefFirst;
};

int main(int argc, char *argv[])
{
	printf("MA3D1 to OBJ Converter\n");
	if (argc >= 2)
	{
		printf("\nConverting %s\n", argv[1]);
		FILE *in;
		in = fopen(argv[1], "rb");

		//Ignore Thumbnail
		fseek(in, 0x480, SEEK_SET);

		numModels = getBE32(in);
		numVerts = getBE32(in);
		numTris = getBE32(in);
		modelOffset = getBE32(in);
		modelSize = getBE32(in);
		printf("Models: %d / Vertexes: %d / Triangles: %d\n", numModels, numVerts, numTris);

		if (numModels <= 0 | numVerts <= 0 | numTris <= 0)
		{
			printf("Invalid file. Stopping.");
			return 1;
		}

		curModelOffset = modelOffset;
		curVerts = 0;
		curTris = 0;

		struct modeldata models[numModels];
		struct vertDef vertex[numVerts];
		struct triDef triangle[numTris];

		//Load Models
		fseek(in, modelOffset, SEEK_SET);
		for (int i = 0; i < numModels; i++)
		{
			//Load Model Def
			models[i].numVerts = getBE32(in);
			getBE32(in); //Skip 4 bytes
			models[i].numTris = getBE32(in);
			getBE32(in); //Skip 4 bytes
			models[i].vertDefOffset = getBE32(in);
			models[i].vertDefSize = getBE32(in);
			getBE32(in); //Skip 4 bytes
			getBE32(in); //Skip 4 bytes
			models[i].triDefOffset = getBE32(in);
			models[i].triDefSize = getBE32(in);
			getBE32(in); //Skip 4 bytes
			getBE32(in); //Skip 4 bytes
			models[i].modelNextOffset = getBE32(in);

			//Print Data
			printf("- Model %d: %d vertex(es), %d triangle(s)\n", i, models[i].numVerts, models[i].numTris);

			//Load Vertex Def
			fseek(in, (modelOffset + models[i].vertDefOffset), SEEK_SET);
			models[i].vertDefFirst = curVerts;
			for (int v = 0; v < models[i].numVerts; v++)
			{
				vertex[curVerts].px = getBE16(in);
				vertex[curVerts].py = getBE16(in);
				vertex[curVerts].pz = getBE16(in);
				vertex[curVerts].nx = get8(in);
				vertex[curVerts].ny = get8(in);
				vertex[curVerts].nz = get8(in);
				vertex[curVerts].unk = get8(in);
				curVerts++;
			}

			//Load Triangle Def
			fseek(in, (modelOffset + models[i].triDefOffset), SEEK_SET);
			models[i].triDefFirst = curTris;
			for (int v = 0; v < models[i].numTris; v++)
			{
				triangle[curTris].v1 = getBE16(in);
				triangle[curTris].v2 = getBE16(in);
				triangle[curTris].v3 = getBE16(in);
				triangle[curTris].unk1 = getBE32(in);
				triangle[curTris].unk2 = getBE32(in);
				curTris++;
			}

			curModelOffset = modelOffset + models[i].modelNextOffset;
			fseek(in, curModelOffset, SEEK_SET);
		}
		fclose(in);

		//Make OBJ file
		FILE *out;
		char outfile[256];
		if (argc == 2)
		{
			sprintf(outfile, "%s.obj", argv[1]);
			out = fopen(outfile, "w");
		}
		else
		{
			sprintf(outfile, argv[2]);
		}
		out = fopen(outfile, "w");
		fprintf(out, "#\n# Converted with MA3D1 to OBJ\n#\n\no %s\n\n", outfile);

		for (int i = 0; i < numModels; i++)
		{
			//Vertexes
			fprintf(out, "# Model %d v\n\n", i);
			for (int v = 0; v < models[i].numVerts; v++)
			{
				fprintf(out, "v %d.0 %d.0 %d.0\n",
					vertex[models[i].vertDefFirst + v].px,
					vertex[models[i].vertDefFirst + v].py,
					vertex[models[i].vertDefFirst + v].pz);
			}
			fprintf(out, "\n");
		}

		fprintf(out, "\n");
		for (int i = 0; i < numModels; i++)
		{
			//Vertex Normals
			fprintf(out, "# Model %d vn\n\n", i);
			for (int v = 0; v < models[i].numVerts; v++)
			{
				fprintf(out, "vn %d.0 %d.0 %d.0\n",
					vertex[models[i].vertDefFirst + v].nx,
					vertex[models[i].vertDefFirst + v].ny,
					vertex[models[i].vertDefFirst + v].nz);
			}
			fprintf(out, "\n");
		}
		fprintf(out, "\n");

		for (int i = 0; i < numModels; i++)
		{
			//Triangles
			fprintf(out, "# Model %d f\n\n", i);
			for (int v = 0; v < models[i].numTris; v++)
			{
				fprintf(out, "f %d//%d %d//%d %d//%d\n",
					triangle[models[i].triDefFirst + v].v1 + models[i].vertDefFirst + 1,
					triangle[models[i].triDefFirst + v].v1 + models[i].vertDefFirst + 1,
					triangle[models[i].triDefFirst + v].v2 + models[i].vertDefFirst + 1,
					triangle[models[i].triDefFirst + v].v2 + models[i].vertDefFirst + 1,
					triangle[models[i].triDefFirst + v].v3 + models[i].vertDefFirst + 1,
					triangle[models[i].triDefFirst + v].v3 + models[i].vertDefFirst + 1);
			}
			fprintf(out, "\n");
		}

		fclose(out);
		printf("\nCreated %s\n", outfile);
	}
	else
	{
		printf("\nUsage: %s <ma3d1 file> (outfile)\n", argv[0]);
	}
	return 0;
}

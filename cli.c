
#include "psbt.h"
#include "string.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

// 70736274ff01009a020000000258e87a21b56daf0c23be8e7070456c336f7cbaa5c8757924f545887bb2abdd750000000000ffffffff838d0427d0ec650a68aa46bb0b098aea4422c071b2ca78352a077959d07cea1d0100000000ffffffff0270aaf00800000000160014d85c2b71d0060b09c9886aeb815e50991dda124d00e1f5050000000016001400aea9a2e5f0f876a588df5546e8742d1d87008f00000000000100bb0200000001aad73931018bd25f84ae400b68848be09db706eac2ac18298babee71ab656f8b0000000048473044022058f6fc7c6a33e1b31548d481c826c015bd30135aad42cd67790dab66d2ad243b02204a1ced2604c6735b6393e5b41691dd78b00f0c5942fb9f751856faa938157dba01feffffff0280f0fa020000000017a9140fb9463421696b82c833af241c78c17ddbde493487d0f20a270100000017a91429ca74f8a08f81999428185c97b5d852e4063f6187650000000104475221029583bf39ae0a609747ad199addd634fa6108559d6c5cd39b4c2183f1ab96e07f2102dab61ff49a14db6a7d02b0cd1fbb78fc4b18312b5b4e54dae4dba2fbfef536d752ae2206029583bf39ae0a609747ad199addd634fa6108559d6c5cd39b4c2183f1ab96e07f10d90c6a4f000000800000008000000080220602dab61ff49a14db6a7d02b0cd1fbb78fc4b18312b5b4e54dae4dba2fbfef536d710d90c6a4f000000800000008001000080010304010000000001012000c2eb0b0000000017a914b7f5faf40e3d40a5a459b1db3535f2b72fa921e88701042200208c2353173743b595dfb4a07b72ba8e42e3797da74e87fe7d9d7497e3b2028903010547522103089dc10c7ac6db54f91329af617333db388cead0c231f723379d1b99030b02dc21023add904f3d6dcf59ddb906b0dee23529b7ffb9ed50e5e86151926860221f0e7352ae2206023add904f3d6dcf59ddb906b0dee23529b7ffb9ed50e5e86151926860221f0e7310d90c6a4f000000800000008003000080220603089dc10c7ac6db54f91329af617333db388cead0c231f723379d1b99030b02dc10d90c6a4f0000008000000080020000800103040100000000220203a9a4c37f5996d3aa25dbac6b570af0650394492942460b354753ed9eeca5877110d90c6a4f000000800000008004000080002202027f6399757d2eff55a136ad02c684b1838b6556e5f1b6b34282a94b6b5005109610d90c6a4f00000080000000800500008000
const unsigned char psbt_example[] = {
  0x70, 0x73, 0x62, 0x74, 0xff, 0x01, 0x00, 0x9a, 0x02, 0x00, 0x00, 0x00,
  0x02, 0x58, 0xe8, 0x7a, 0x21, 0xb5, 0x6d, 0xaf, 0x0c, 0x23, 0xbe, 0x8e,
  0x70, 0x70, 0x45, 0x6c, 0x33, 0x6f, 0x7c, 0xba, 0xa5, 0xc8, 0x75, 0x79,
  0x24, 0xf5, 0x45, 0x88, 0x7b, 0xb2, 0xab, 0xdd, 0x75, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x83, 0x8d, 0x04, 0x27, 0xd0, 0xec,
  0x65, 0x0a, 0x68, 0xaa, 0x46, 0xbb, 0x0b, 0x09, 0x8a, 0xea, 0x44, 0x22,
  0xc0, 0x71, 0xb2, 0xca, 0x78, 0x35, 0x2a, 0x07, 0x79, 0x59, 0xd0, 0x7c,
  0xea, 0x1d, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x02,
  0x70, 0xaa, 0xf0, 0x08, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x14, 0xd8,
  0x5c, 0x2b, 0x71, 0xd0, 0x06, 0x0b, 0x09, 0xc9, 0x88, 0x6a, 0xeb, 0x81,
  0x5e, 0x50, 0x99, 0x1d, 0xda, 0x12, 0x4d, 0x00, 0xe1, 0xf5, 0x05, 0x00,
  0x00, 0x00, 0x00, 0x16, 0x00, 0x14, 0x00, 0xae, 0xa9, 0xa2, 0xe5, 0xf0,
  0xf8, 0x76, 0xa5, 0x88, 0xdf, 0x55, 0x46, 0xe8, 0x74, 0x2d, 0x1d, 0x87,
  0x00, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xbb, 0x02, 0x00,
  0x00, 0x00, 0x01, 0xaa, 0xd7, 0x39, 0x31, 0x01, 0x8b, 0xd2, 0x5f, 0x84,
  0xae, 0x40, 0x0b, 0x68, 0x84, 0x8b, 0xe0, 0x9d, 0xb7, 0x06, 0xea, 0xc2,
  0xac, 0x18, 0x29, 0x8b, 0xab, 0xee, 0x71, 0xab, 0x65, 0x6f, 0x8b, 0x00,
  0x00, 0x00, 0x00, 0x48, 0x47, 0x30, 0x44, 0x02, 0x20, 0x58, 0xf6, 0xfc,
  0x7c, 0x6a, 0x33, 0xe1, 0xb3, 0x15, 0x48, 0xd4, 0x81, 0xc8, 0x26, 0xc0,
  0x15, 0xbd, 0x30, 0x13, 0x5a, 0xad, 0x42, 0xcd, 0x67, 0x79, 0x0d, 0xab,
  0x66, 0xd2, 0xad, 0x24, 0x3b, 0x02, 0x20, 0x4a, 0x1c, 0xed, 0x26, 0x04,
  0xc6, 0x73, 0x5b, 0x63, 0x93, 0xe5, 0xb4, 0x16, 0x91, 0xdd, 0x78, 0xb0,
  0x0f, 0x0c, 0x59, 0x42, 0xfb, 0x9f, 0x75, 0x18, 0x56, 0xfa, 0xa9, 0x38,
  0x15, 0x7d, 0xba, 0x01, 0xfe, 0xff, 0xff, 0xff, 0x02, 0x80, 0xf0, 0xfa,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x17, 0xa9, 0x14, 0x0f, 0xb9, 0x46, 0x34,
  0x21, 0x69, 0x6b, 0x82, 0xc8, 0x33, 0xaf, 0x24, 0x1c, 0x78, 0xc1, 0x7d,
  0xdb, 0xde, 0x49, 0x34, 0x87, 0xd0, 0xf2, 0x0a, 0x27, 0x01, 0x00, 0x00,
  0x00, 0x17, 0xa9, 0x14, 0x29, 0xca, 0x74, 0xf8, 0xa0, 0x8f, 0x81, 0x99,
  0x94, 0x28, 0x18, 0x5c, 0x97, 0xb5, 0xd8, 0x52, 0xe4, 0x06, 0x3f, 0x61,
  0x87, 0x65, 0x00, 0x00, 0x00, 0x01, 0x04, 0x47, 0x52, 0x21, 0x02, 0x95,
  0x83, 0xbf, 0x39, 0xae, 0x0a, 0x60, 0x97, 0x47, 0xad, 0x19, 0x9a, 0xdd,
  0xd6, 0x34, 0xfa, 0x61, 0x08, 0x55, 0x9d, 0x6c, 0x5c, 0xd3, 0x9b, 0x4c,
  0x21, 0x83, 0xf1, 0xab, 0x96, 0xe0, 0x7f, 0x21, 0x02, 0xda, 0xb6, 0x1f,
  0xf4, 0x9a, 0x14, 0xdb, 0x6a, 0x7d, 0x02, 0xb0, 0xcd, 0x1f, 0xbb, 0x78,
  0xfc, 0x4b, 0x18, 0x31, 0x2b, 0x5b, 0x4e, 0x54, 0xda, 0xe4, 0xdb, 0xa2,
  0xfb, 0xfe, 0xf5, 0x36, 0xd7, 0x52, 0xae, 0x22, 0x06, 0x02, 0x95, 0x83,
  0xbf, 0x39, 0xae, 0x0a, 0x60, 0x97, 0x47, 0xad, 0x19, 0x9a, 0xdd, 0xd6,
  0x34, 0xfa, 0x61, 0x08, 0x55, 0x9d, 0x6c, 0x5c, 0xd3, 0x9b, 0x4c, 0x21,
  0x83, 0xf1, 0xab, 0x96, 0xe0, 0x7f, 0x10, 0xd9, 0x0c, 0x6a, 0x4f, 0x00,
  0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x22,
  0x06, 0x02, 0xda, 0xb6, 0x1f, 0xf4, 0x9a, 0x14, 0xdb, 0x6a, 0x7d, 0x02,
  0xb0, 0xcd, 0x1f, 0xbb, 0x78, 0xfc, 0x4b, 0x18, 0x31, 0x2b, 0x5b, 0x4e,
  0x54, 0xda, 0xe4, 0xdb, 0xa2, 0xfb, 0xfe, 0xf5, 0x36, 0xd7, 0x10, 0xd9,
  0x0c, 0x6a, 0x4f, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x01,
  0x00, 0x00, 0x80, 0x01, 0x03, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x01, 0x20, 0x00, 0xc2, 0xeb, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x17, 0xa9,
  0x14, 0xb7, 0xf5, 0xfa, 0xf4, 0x0e, 0x3d, 0x40, 0xa5, 0xa4, 0x59, 0xb1,
  0xdb, 0x35, 0x35, 0xf2, 0xb7, 0x2f, 0xa9, 0x21, 0xe8, 0x87, 0x01, 0x04,
  0x22, 0x00, 0x20, 0x8c, 0x23, 0x53, 0x17, 0x37, 0x43, 0xb5, 0x95, 0xdf,
  0xb4, 0xa0, 0x7b, 0x72, 0xba, 0x8e, 0x42, 0xe3, 0x79, 0x7d, 0xa7, 0x4e,
  0x87, 0xfe, 0x7d, 0x9d, 0x74, 0x97, 0xe3, 0xb2, 0x02, 0x89, 0x03, 0x01,
  0x05, 0x47, 0x52, 0x21, 0x03, 0x08, 0x9d, 0xc1, 0x0c, 0x7a, 0xc6, 0xdb,
  0x54, 0xf9, 0x13, 0x29, 0xaf, 0x61, 0x73, 0x33, 0xdb, 0x38, 0x8c, 0xea,
  0xd0, 0xc2, 0x31, 0xf7, 0x23, 0x37, 0x9d, 0x1b, 0x99, 0x03, 0x0b, 0x02,
  0xdc, 0x21, 0x02, 0x3a, 0xdd, 0x90, 0x4f, 0x3d, 0x6d, 0xcf, 0x59, 0xdd,
  0xb9, 0x06, 0xb0, 0xde, 0xe2, 0x35, 0x29, 0xb7, 0xff, 0xb9, 0xed, 0x50,
  0xe5, 0xe8, 0x61, 0x51, 0x92, 0x68, 0x60, 0x22, 0x1f, 0x0e, 0x73, 0x52,
  0xae, 0x22, 0x06, 0x02, 0x3a, 0xdd, 0x90, 0x4f, 0x3d, 0x6d, 0xcf, 0x59,
  0xdd, 0xb9, 0x06, 0xb0, 0xde, 0xe2, 0x35, 0x29, 0xb7, 0xff, 0xb9, 0xed,
  0x50, 0xe5, 0xe8, 0x61, 0x51, 0x92, 0x68, 0x60, 0x22, 0x1f, 0x0e, 0x73,
  0x10, 0xd9, 0x0c, 0x6a, 0x4f, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
  0x80, 0x03, 0x00, 0x00, 0x80, 0x22, 0x06, 0x03, 0x08, 0x9d, 0xc1, 0x0c,
  0x7a, 0xc6, 0xdb, 0x54, 0xf9, 0x13, 0x29, 0xaf, 0x61, 0x73, 0x33, 0xdb,
  0x38, 0x8c, 0xea, 0xd0, 0xc2, 0x31, 0xf7, 0x23, 0x37, 0x9d, 0x1b, 0x99,
  0x03, 0x0b, 0x02, 0xdc, 0x10, 0xd9, 0x0c, 0x6a, 0x4f, 0x00, 0x00, 0x00,
  0x80, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x80, 0x01, 0x03, 0x04,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x22, 0x02, 0x03, 0xa9, 0xa4, 0xc3, 0x7f,
  0x59, 0x96, 0xd3, 0xaa, 0x25, 0xdb, 0xac, 0x6b, 0x57, 0x0a, 0xf0, 0x65,
  0x03, 0x94, 0x49, 0x29, 0x42, 0x46, 0x0b, 0x35, 0x47, 0x53, 0xed, 0x9e,
  0xec, 0xa5, 0x87, 0x71, 0x10, 0xd9, 0x0c, 0x6a, 0x4f, 0x00, 0x00, 0x00,
  0x80, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x80, 0x00, 0x22, 0x02,
  0x02, 0x7f, 0x63, 0x99, 0x75, 0x7d, 0x2e, 0xff, 0x55, 0xa1, 0x36, 0xad,
  0x02, 0xc6, 0x84, 0xb1, 0x83, 0x8b, 0x65, 0x56, 0xe5, 0xf1, 0xb6, 0xb3,
  0x42, 0x82, 0xa9, 0x4b, 0x6b, 0x50, 0x05, 0x10, 0x96, 0x10, 0xd9, 0x0c,
  0x6a, 0x4f, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x05, 0x00,
  0x00, 0x80, 0x00
};


void print_json_rec(void *user_data, struct psbt_record *rec) {
	printf("{\n    ");
	printf("\"tx\": \"");

	/* for (int i = 0; i < rec->) */

		printf("\"type\": \"%s\"", psbt_type_tostr(rec->type, rec->scope));
}

void print_rec(void *user_data, struct psbt_record *rec) {
	(void)user_data;
	const char *type_str = psbt_type_tostr(rec->type, rec->scope);
	printf("%s (%d)\n", type_str, rec->type);

}

int main(int argc, char *argv[])
{
	struct psbt tx;
	static unsigned char buffer[2048];
	enum psbt_result res;

	psbt_init(&tx, buffer, 2048);

	res = psbt_read(psbt_example, ARRAY_SIZE(psbt_example), &tx, print_rec, NULL);

	if (res != PSBT_OK) {
		printf("error (%d): %s\n", res, psbt_errmsg);
		return 1;
	}

	return 0;
}

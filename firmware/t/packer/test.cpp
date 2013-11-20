#include "IrPacker.h"
#include "nanotap.h"
#include "utils.h"
#include "string.h"

// Arduino can load from EEPROM, but we can't
void fillTree(IrPacker *packer) {
    uint16_t tree[TREE_SIZE] = {
        30, 31, 32, 33, 34, 35, 36, 38,
        39, 40, 42, 43, 45, 46, 48, 50,
        52, 53, 55, 57, 59, 61, 63, 66,
        68, 70, 73, 75, 78, 81, 84, 87,
        90, 93, 96, 100, 103, 107, 110, 114,
        118, 122, 127, 131, 136, 141, 146, 151,
        156, 161, 167, 173, 179, 185, 192, 198,
        205, 213, 220, 228, 236, 244, 253, 262,
        271, 280, 290, 300, 311, 322, 333, 345,
        357, 369, 382, 395, 409, 424, 439, 454,
        470, 486, 503, 521, 539, 558, 578, 598,
        619, 640, 663, 686, 710, 735, 761, 787,
        815, 843, 873, 904, 935, 968, 1002, 1037,
        1073, 1111, 1150, 1190, 1232, 1275, 1319, 1366,
        1413, 1463, 1514, 1567, 1622, 1679, 1738, 1798,
        1861, 1927, 1994, 2064, 2136, 2211, 2288, 2368,
        2451, 2537, 2626, 2718, 2813, 2911, 3013, 3119,
        3228, 3341, 3458, 3579, 3704, 3834, 3968, 4107,
        4251, 4400, 4554, 4713, 4878, 5049, 5226, 5408,
        5598, 5794, 5997, 6206, 6424, 6648, 6881, 7122,
        7371, 7629, 7896, 8173, 8459, 8755, 9061, 9379,
        9707, 10047, 10398, 10762, 11139, 11529, 11932, 12350,
        12782, 13230, 13693, 14172, 14668, 15181, 15713, 16263,
        16832, 17421, 18031, 18662, 19315, 19991, 20691, 21415,
        22165, 22940, 23743, 24574, 25434, 26325, 27246, 28200,
        29187, 30208, 31265, 32360, 33492, 34665, 35878, 37134,
        38433, 39779, 41171, 42612, 44103, 45647, 47245, 48898,
        50610, 52381, 54214, 56112, 58076, 60108, 62212, 64390
    };
    memcpy( packer->tree, tree, sizeof(tree) );
}

int main() {
    ok( 1, "ok" );

    {
        IrPacker packer;
        fillTree( &packer );
        uint16_t input = 17946; // 0x461A

        uint8_t packed = packer.pack( input );
        printf( "input: %d 0x%x\n", input, input );
        printf( "packd: %d 0x%x\n", packed, packed );

        ok( packed == 215 );
    }

    {
        IrPacker packer;
        fillTree( &packer );
        uint16_t input = 30;

        uint8_t packed = packer.pack( input );
        printf( "input: %d 0x%x\n", input, input );
        printf( "packd: %d 0x%x\n", packed, packed );

        ok( packed == 30 );
    }

    {
        IrPacker packer;
        fillTree( &packer );
        uint16_t input = 65000;

        uint8_t packed = packer.pack( input );
        printf( "input: %d 0x%x\n", input, input );
        printf( "packd: %d 0x%x\n", packed, packed );

        ok( packed == 253 );
    }

    {
        IrPacker packer;
        fillTree( &packer );
        uint16_t input = 60108;

        uint8_t packed = packer.pack( input );
        printf( "input: %d 0x%x\n", input, input );
        printf( "packd: %d 0x%x\n", packed, packed );

        ok( packed == 251 );
    }

    {
        IrPacker packer;
        fillTree( &packer );
        uint16_t input;
        char buf[100];

        for (uint8_t i=0; i<224; i++) {
            input = packer.tree[ i ];
            uint8_t packed = packer.pack( input );
            sprintf( buf, "%d (0x%x) --pack-> %d (0x%x)", input, input, packed, packed );
            ok( packed == i + 30, buf );

            uint16_t unpacked = packer.unpack( packed );
            sprintf( buf, "%d (0x%x) --unpack-> %d (0x%x)", packed, packed, unpacked, unpacked );
            ok( unpacked == input, buf );
        }
    }

    done_testing();
}

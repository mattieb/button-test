#include <tonc.h>

#define DOWN(x) ~(REG_KEYINPUT) & (x)
#define UP(x) (REG_KEYINPUT) & (x)

int main(void)
{
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);
	tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
	tte_init_con();

	tte_set_pos(16, 144);
	tte_write("Button Test Advance");
	tte_set_pos(16, 152);
	tte_write("mattiebee.dev/button-test");

	tte_set_pos(48, 24);
	tte_write("><");

	tte_set_pos(48, 96);
	tte_write("><");

	while (true)
	{
		u8 b = 0;
		u8 a = 0;
		u8 l = 0;
		u8 r = 0;
		u8 select = 0;
		u8 start = 0;

		u8 up = 0;
		u8 left = 0;
		u8 right = 0;
		u8 down = 0;

		u8 up_only = 0;
		u8 up_left = 0;
		u8 up_right = 0;
		u8 left_only = 0;
		u8 right_only = 0;
		u8 down_left = 0;
		u8 down_right = 0;
		u8 down_only = 0;

		while (true)
		{
			if (DOWN(KEY_SELECT) && DOWN(KEY_START))
				break;

			if (DOWN(KEY_A))
				a++;
			if (DOWN(KEY_B))
				b++;
			if (DOWN(KEY_L))
				l++;
			if (DOWN(KEY_R))
				r++;
			if (DOWN(KEY_SELECT))
				select++;
			if (DOWN(KEY_START))
				start++;

			if (DOWN(KEY_UP))
				up++;
			if (DOWN(KEY_LEFT))
				left++;
			if (DOWN(KEY_RIGHT))
				right++;
			if (DOWN(KEY_DOWN))
				down++;

			if (DOWN(KEY_UP) && UP(KEY_LEFT) && UP(KEY_RIGHT))
				up_only++;
			if (DOWN(KEY_UP) && DOWN(KEY_LEFT))
				up_left++;
			if (DOWN(KEY_UP) && DOWN(KEY_RIGHT))
				up_right++;

			if (DOWN(KEY_LEFT) && UP(KEY_UP) && UP(KEY_DOWN))
				left_only++;
			if (DOWN(KEY_RIGHT) && UP(KEY_UP) && UP(KEY_DOWN))
				right_only++;

			if (DOWN(KEY_DOWN) && UP(KEY_LEFT) && UP(KEY_RIGHT))
				down_only++;
			if (DOWN(KEY_DOWN) && DOWN(KEY_LEFT))
				down_left++;
			if (DOWN(KEY_DOWN) && DOWN(KEY_RIGHT))
				down_right++;

			tte_set_pos(136, 0);
			tte_printf("L %02x   R %02x", l, r);
			tte_set_pos(136, 8);
			tte_printf("B %02x   A %02x", b, a);

			tte_set_pos(136, 32);
			tte_printf("Select   %02x", select);
			tte_set_pos(136, 40);
			tte_printf("Start    %02x", start);

			tte_set_pos(48, 0);
			tte_printf("%02x", up);
			tte_set_pos(16, 24);
			tte_printf("%02x", left);
			tte_set_pos(80, 24);
			tte_printf("%02x", right);
			tte_set_pos(48, 48);
			tte_printf("%02x", down);

			tte_set_pos(16, 72);
			tte_printf("%02x", up_left);
			tte_set_pos(48, 72);
			tte_printf("%02x", up_only);
			tte_set_pos(80, 72);
			tte_printf("%02x", up_right);

			tte_set_pos(16, 96);
			tte_printf("%02x", left_only);
			tte_set_pos(80, 96);
			tte_printf("%02x", right_only);

			tte_set_pos(16, 120);
			tte_printf("%02x", down_left);
			tte_set_pos(48, 120);
			tte_printf("%02x", down_only);
			tte_set_pos(80, 120);
			tte_printf("%02x", down_right);

			VBlankIntrWait();
		}
	}

	return 0;
}

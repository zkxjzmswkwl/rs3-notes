
char* buildJagexPacket(Packet* packet, char opcode, Isaac* isaac)
{
    if (isaac->bytesRemaining == 0) {
        isaacGenerate(isaac);
        isaac->bytesRemaining = 0x100;
    }
    isaac->bytesRemaining -= 1;
    packet->len += 1;
    //                                                                                     + or - here idfk forgot will check later
    packet->buffer[packet->len] = (char)isaac->cipherResult[isaac->bytesRemaining + 1] + opcode;
    return packet->buffer;
}

struct __declspec(align(8)) Packet
{
	uint16_t a;
	uint16_t b;
	uint16_t c;
	uint16_t d;
	uint32_t e;
	uint32_t f; 
	char* buffer;
	uint64_t len;
};

struct Isaac {
    uint8_t bytesRemaining;
    unsigned int cipherResult[256];
    unsigned int mm[256];
    unsigned int aa;
    unsigned int bb;
    unsigned int cc;
};


// 12 bytes in size, 10 bytes apart.
struct Skill {
	int totalExp;
	int maxLevel;
	int curLevel;
};

std::vector<unsigned int> skillLocOffsets = { 0x38, 0xB40, 0x20, 0x1B8, 0x190, 0x10, 0x0 };

struct SkillTree {
	char imreallygay[0xC];
	Skill attack;
	char imgay[0xC];
	Skill defense;
	char stillgay[0xC];
	Skill strength;
	char mightbestraight[0xC];
	Skill constitution;
	char nahimgay[0xC];
	Skill ranged;
	char teeth[0xC];
	Skill prayer;
	char american[0xC];
	Skill magic;
	char mcdouble[0xC];
	Skill cooking;
	char bigmac[0xC];
	Skill woodcutting;
	char cocacola[0xC];
	Skill fletching;
	char burgerking[0xC];
	Skill fishing;
	char crown[0xC];
	Skill firemaking;
	char ballsack[0xC];
	Skill crafting;
	char renob[0xC];
	Skill smithing;
	char boner[0xC];
	Skill mining;
	char runningoutofideas[0xC];
	Skill herblore;
	char brexit[0xC];
	Skill agility;
	char unabomberwasright[0xC];
	Skill thieving;
	char chicfila[0xC];
	Skill slayer;
	char varrock[0xC];
	Skill farming;
	char lumbridge[0xC];
	Skill runecrafting;
	char ardougne[0xC];
	Skill hunter;
	char morytania[0xC];
	Skill construction;
	char falador[0xC];
	Skill summoning;
	char daemonheim[0xC];
	Skill dungeoneering;
	char yanille[0xC];
	Skill divination;
	char menaphos[0xC];
	Skill invention;
	char draynor[0xC];
	Skill archaeology;
};

SkillTree* loadSkills(uintptr_t memoryBase) {
	return (SkillTree*)(iterateChain((uintptr_t)(memoryBase + 0x00BD9BC8), skillLocOffsets));
}


void doConsecutiveActions(
	Skill* relatedSkill,
	int repeatCount,
	std::function<void(int invIndex)> delegate
) {
	int prevExp = 0;
	int actionsDone = 0;

	while (actionsDone <= repeatCount) {
		if (relatedSkill->totalExp != prevExp) {
			std::cout << "Prv EXP\t" << prevExp << "\nNow EXP\t" << relatedSkill->totalExp << "\n\n";
			delegate(actionsDone);
			prevExp = relatedSkill->totalExp;
			actionsDone++;
		}
		Sleep(5);
	}
}

#include <item.h>
#include <vector>

void Item::printItemSprite() {
	for (int i = 0; i < itemSprite.size(); i++) {
		std::cout << "          " << itemSprite.at(i) << "          " << std::endl;
	}
}

// Accessors

std::string Item::getItemName() {
	return itemName;
}

std::string Item::getItemType() {
	return itemType;
}

int Item::getItemDam() {
	return itemDam;
}

int Item::getItemDT() {
	return itemDT;
}

int Item::getItemValue() {
	return itemValue;
}



// Mutators

void Item::setItemName(std::string setItemName) {
	itemName = setItemName;
}

void Item::setItemSprite(std::string tempFileLoc) {
	
	std::ifstream tempFile(fs::current_path().string() + tempFileLoc);

	std::vector<std::string> tempSprite;
	std::string tempSpriteLine;

	while (std::getline(tempFile, tempSpriteLine)) {
		// Extract data from each column and store in variables
		std::istringstream issSprite(tempSpriteLine);
		std::getline(issSprite, tempSpriteLine);
		tempSprite.push_back(tempSpriteLine);
		// TEST Print the extracted data to the console
		// std::cout << "s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << ", s4: " << s4 << std::endl;
	}
	tempFile.close();
	itemSprite = tempSprite;
	tempSprite.clear();
}

Item::Item()
{
	itemDam = 0;
	itemDT = 0;
	itemValue = 0;
	itemName = "item";
	itemType = 'X';
	itemSprite = {};
}

Item::~Item()
{
}



// getItemSprite contains all item sprites

//   ______________________________________________ 
//  |                  :!~    .7!.                 |
//  |                  : 7BJ!PB^ :                 |
//  |                  .75B#&&#P~.                 |
//  |               .^?P##GJ#&&&#BY~               |
//  |              ?55PB##GBB####BGG5!             |
//  |            :5BB#&&&#&@&&&&#BGBBG?            |
//  |           ~G##5#&&P#@@@#&@&##&#BBP.          |
//  |          !GB#PGB&BG@@&&G#&&#P&#BBBG^         |
//  |         !PPGGGBPGG#GBPBG###BGGPGPPPP:        |
//  |        .5PPB#BBB#&&&&####&&#BBBBBGGGJ        |
//  |        7PPG###G#&&#&&@#&@&&B&&#GB#PPP^       |
//  |       .5PGB#BG#&&&#&@@#&@&#B&&#GBBGPG?       |
//  |       !Y55PGGBBBB###&####BBB##PPGPPP55.      |
//  |       7PPP5GGGGGBBBBBGBBGGGB#BGGGPPP5P:      |
//  |       ?PGGBBGBB#B#BB##BBBGGGBBBGGGBGPP:      |
//  |       JPGGB#BB####&&#&&#GB##BBBGG#BBP5:      |
//  |       !5PGGBBB#BB#&&####B&##B#BBBBGB5J.      |
//  |       :J::!?YPPGB####BBGB#&#GGP55?!:7J       |
//  |       .Y.      ..:::^^^^^^^....     77       |
//  |        J^                           J~       |
//  |        7!                          .Y.       |
//  |        7!                          .Y.       |
//  |        :J                          ^?        |
//  |         J.                         ?~        |
//  |         ^!                        .?         |
//  |          .                        :.         |
//  |______________________________________________|
//   TUSK HELM                                      
//
//
//
//   ______________________________________________
//  |                                              |
//  |                     ..,,,,                   |
//  |                 .,*/(((#((#(*.               |
//  |              .,/(##%%%%%%###(/(/.            |
//  |             *((##%%%%%%%%%#(((%#(/,          |
//  |           ./(#%%%%%%%%%%%%%&###%%((*.        |
//  |          *(##%%%%%%%%%%%%%%%%#%%%%##/,       |
//  |         *(##%%%%%%%&&%%%%%%%%&#%&%%%#(,      |
//  |        */(#%%%%%%%%&%&%%%%####((%&%%%#(.     |
//  |       %/((#%%%%%%%%%%%&&&%%%%%###&&%%%#(,    |
//  |       ,/(##%%(%%&&&%%&&&&%#((/*//(&&%%%#*    |
//  |       ,/(#%%%%%%%&&&&&&%%%#%&&**//&&%%##(,   |
//  |       ,/(,#%%*             ,(,,,*/&&         |
//  |       */(#%(/%%%%%%%%%##((/*,,,,,/&%%%#(/.   |
//  |       *(##%%%%%%%%%%%%%%%#((/,,,,&&%%#(*.    |
//  |       *(#%%%%%%%%%%%%%%%##((/,*,,&%%%#(*     |
//  |      .,(#%%%%%%%%%%%%%%% #((/,*,*%%%%#(*     |
//  |      ,/(##%%%%.%%%%%%%####(//**,%%%%##/,.    |
//  |     ,/(###%%%%%%%%%%%%%###((//*,%#%##(/,     |
//  |    ,(#,###/###%%%%%%%%%####(/#**%%%%*(*,     |
//  |     #############%%% %%####(//*%#%%#(/,.     |
//  |         ,######(#%%%%%%%%%#////#(&#((/,.     |
//  |             ((#((((########/(/(*((((/,.      |
//  |                 #((((((####(/#*///*,,        |
//  |                      (((((((((****           |
//  |                            ((/               |
//  |______________________________________________|
//   STEEL HELM
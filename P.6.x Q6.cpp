#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <vector>
enum class CardRank
{
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,

	MAX_RANK
};

enum class CardSuit
{
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES,
	MAX_SUIT
};

struct Card
{
	CardRank rank{};
	CardSuit suit{};
};

void printCard(Card card)
{
	switch (card.rank)
	{
	case CardRank::TWO:
		std::cout << '2';
		break;
	case CardRank::THREE:
		std::cout << '3';
		break;
	case CardRank::FOUR:
		std::cout << '4';
		break;
	case CardRank::FIVE:
		std::cout << '5';
		break;
	case CardRank::SIX:
		std::cout << '6';
		break;
	case CardRank::SEVEN:
		std::cout << '7';
		break;
	case CardRank::EIGHT:
		std::cout << '8';
		break;
	case CardRank::NINE:
		std::cout << '9';
		break;
	case CardRank::TEN:
		std::cout << 'T';
		break;
	case CardRank::JACK:
		std::cout << 'J';
		break;
	case CardRank::QUEEN:
		std::cout << 'Q';
		break;
	case CardRank::KING:
		std::cout << 'K';
		break;
	case CardRank::ACE:
		std::cout << 'A';
		break;
	default:
		std::cout << '?';
	}

	switch (card.suit)
	{
	case CardSuit::CLUBS:
		std::cout << 'C';
		break;
	case CardSuit::DIAMONDS:
		std::cout << 'D';
		break;
	case CardSuit::HEARTS:
		std::cout << 'H';
		break;
	case CardSuit::SPADES:
		std::cout << 'S';
		break;
	default:
		std::cout << '?';
	}
}

std::array<Card, 52> createDeck()
{
	std::array<Card, 52> deck;
	std::array<Card, 52>::size_type card{ 0 };
	for (int suitCounter{ 0 }; suitCounter < static_cast<int>(CardSuit::MAX_SUIT); ++suitCounter)
	{
		for (int rankCounter{ 0 }; rankCounter < static_cast<int>(CardRank::MAX_RANK); ++rankCounter)
		{
			deck[card].rank = static_cast<CardRank>(rankCounter);
			deck[card].suit = static_cast<CardSuit>(suitCounter);
			++card;
		}
	}
	return deck;
}
void printHand(std::vector<Card> deck)
{
	for (auto& element : deck)
	{
		printCard(element);
		std::cout << ' ';
	}
}

int getCardValue(const Card& card)
{
	if (static_cast<int>(card.rank) <= 7)
		return static_cast<int>(card.rank) + 2;
	if (static_cast<int>(card.rank) <= 11)
		return 10;
	if (static_cast<int>(card.rank) == 12)
		return 11;
	else
		return 0;
}

bool getResponse()
{
	char answer{};
	
	while (true)
	{
		std::cout << "Do you want to hit or stay? (h/s) ";
		std::cin >> answer;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		switch (answer)
		{
		case 'h':
			std::cin.ignore(32767, '\n');
			return true;
		case 's':
			std::cin.ignore(32767, '\n');
			return false;
		default:
			std::cin.ignore(32767, '\n');
		}
	}

}

void playBlackjack(std::array<Card, 52> deck)
{
	std::array<Card, 52>::size_type deckIndex{ 0 };
	int dealerSum{ 0 };
	int playerSum{ 0 };
	int playerAceCounter{ 0 };
	int dealerAceCounter{ 0 };
	std::vector<Card> playerHand;
	std::vector<Card> dealerHand;
	std::size_t playerIndex{ 1 };
	std::size_t dealerIndex{ 1 };
	playerHand.resize(playerIndex);
	playerHand.at(playerIndex - 1) = deck[deckIndex];
	playerSum = getCardValue(deck[deckIndex]);
	if (getCardValue(deck[deckIndex]) == 11)
	{
		++playerAceCounter;
	}
	++deckIndex;
	++playerIndex;
	playerHand.resize(playerIndex);
	playerHand.at(playerIndex - 1) = deck[deckIndex];
	playerSum += getCardValue(deck[deckIndex]);
	if (getCardValue(deck[deckIndex]) == 11)
	{
		++playerAceCounter;
	}
	++deckIndex;
	++playerIndex;
	dealerHand.resize(dealerIndex);
	dealerHand.at(dealerIndex - 1) = deck[deckIndex];
	dealerSum = getCardValue(deck[deckIndex]);
	if (getCardValue(deck[deckIndex]) == 11)
	{
		++dealerAceCounter;
	}
	++deckIndex;
	++dealerIndex;
	if (playerAceCounter > 0 && playerSum > 21)
	{
		while (playerAceCounter > 0 && playerSum > 21)
		{
			playerSum -= 10;
			--playerAceCounter;
		}
	}
	std::cout << "\nDealer has " << dealerSum << ": ";
	printHand(dealerHand);
	std::cout << '\n';
	std::cout << "You have " << playerSum << ": ";
	printHand(playerHand);
	std::cout << "\n\n";

	while (getResponse())
	{
		playerHand.resize(playerIndex);
		playerHand.at(playerIndex - 1) = deck[deckIndex];
		playerSum += getCardValue(deck[deckIndex]);
		if (getCardValue(deck[deckIndex]) == 11)
		{
			++playerAceCounter;
		}
		++deckIndex;
		++playerIndex;
		if (playerAceCounter > 0 && playerSum > 21)
		{
			while (playerAceCounter > 0 && playerSum > 21)
			{
				playerSum -= 10;
				--playerAceCounter;
			}
		}
		std::cout << "\nDealer has " << dealerSum << ": ";
		printHand(dealerHand);
		std::cout << '\n';
		std::cout << "You have " << playerSum << ": ";
		printHand(playerHand);
		std::cout << "\n\n";
		if (playerSum > 21)
		{
			std::cout << "Yikes! You busted. You lost.\n";
			return;
		}
	}
	
	while (dealerSum < 17)
	{
		dealerHand.resize(dealerIndex);
		dealerHand.at(dealerIndex - 1) = deck[deckIndex];
		dealerSum += getCardValue(deck[deckIndex]);
		if (getCardValue(deck[deckIndex]) == 11)
		{
			++dealerAceCounter;
		}
		++deckIndex;
		++dealerIndex;
		if (dealerAceCounter > 0 && dealerSum > 21)
		{
			while (playerAceCounter > 0 && dealerSum > 21)
			{
				dealerSum -= 10;
				--dealerAceCounter;
			}
		}
		std::cout << "\nDealer has " << dealerSum << ": ";
		printHand(dealerHand);
		std::cout << '\n';
		std::cout << "You have " << playerSum << ": ";
		printHand(playerHand);
		std::cout << "\n\n";
	}
	
	if (dealerSum > 21)
	{
		std::cout << "The dealer busted! You win!!!\n\n";
		return;
	}
	if (dealerSum > playerSum)
	{
		std::cout << "The dealer wins.\n\n";
		return;
	}
	if (dealerSum < playerSum)
	{
		std::cout << "Congrats! You won!!!\n\n";
		return;
	}
	else
		std::cout << "Well, it appears that you have tied.\n\n";
}

bool playAgain()
{
	char answer{};

	while (true)
	{
		std::cout << "Do you want to play again? (y/n) ";
		std::cin >> answer;
		
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		switch (answer)
		{
		case 'y':
			std::cin.ignore(32767, '\n');
			return true;
		case 'n':
			std::cin.ignore(32767, '\n');
			return false;
		default:
			std::cin.ignore(32767, '\n');
		}
	}
}

int main()
{
	do
	{
	auto deck{ createDeck() };
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(deck.begin(), deck.end(), g);
	playBlackjack(deck);
	} while (playAgain());
	return 0;
}
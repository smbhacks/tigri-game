#pragma once
#include <cstdint>
#include "Controller.h"
#include "memtrace.h"

// The core uses these so we can seperate the SDL and test builds easily

/// <summary>
/// Rendszerszintű segédfüggvényeket és alapvető grafikai/eseménykezelő osztályokat tömörítő osztály.
/// </summary>
class SystemUtils
{
private:
	static inline bool shutdownRequestedFlag = false;

public:
	/// <summary>
	/// Egy téglalapot leíró struktúra koordinátákkal és méretekkel.
	/// </summary>
	template<typename T>
	struct Rect {
		T x;
		T y;
		T w;
		T h;
	};

	/// <summary>
	/// Egy RGBA színkomponenseket tároló struktúra.
	/// </summary>
	struct Color {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r(r), g(g), b(b), a(a) {}
		Color() : r(0), g(0), b(0), a(255) {}
	};

	/// <summary>
	/// Egy általános játékbeli erőforrást és annak elérési útját kezelő alaposztály.
	/// </summary>
	class Resource
	{
	protected:
		const char* m_path;
		void* m_implementedInstance = nullptr;
	public:
		/// <summary>
		/// Erőforrás konstruktor az elérési út megadásával.
		/// </summary>
		Resource(const char* path)
			: m_path(path)
		{
		}

		/// <summary>
		/// Visszaadja a mögöttes implementációs példány mutatóját.
		/// </summary>
		void* getInstance() const { return m_implementedInstance; }

		/// <summary>
		/// Visszaadja az erőforrás elérési útját.
		/// </summary>
		const char* getPath() const { return m_path; }
	};

	/// <summary>
	/// Grafikus textúra erőforrás osztály.
	/// </summary>
	class Texture : public Resource
	{
	public:
		Texture(const char* path);
		~Texture();
	};

	/// <summary>
	/// Háttérzene erőforrás osztály.
	/// </summary>
	class Music : public Resource
	{
	public:
		/// <summary>
		/// Elindítja a zene lejátszását a megadott ismétlésszámmal.
		/// </summary>
		void playMusic(int loops);
		Music(const char* path);
		~Music();
	};

	/// <summary>
	/// Betűtípus erőforrás osztály.
	/// </summary>
	class Font : public Resource
	{
	public:
		Font(const char* path, int size);
		~Font();
	};

	/// <summary>
	/// Szövegek generálásáért és képernyőre rajzolásáért felelős osztály.
	/// </summary>
	class Text : public Resource
	{
	private:
		int m_textWidth;
		int m_textHeight;
	public:
		Text(const Font& font, const char* string, const Color& color);
		~Text();

		/// <summary>
		/// Kirajzolja a szöveget a megadott célterületre és eltolással.
		/// </summary>
		void render(const Rect<int>& dstRect, int xOffset = 0, int yOffset = 0);

		/// <summary>
		/// Visszaadja a generált szöveg szélességét pixelben.
		/// </summary>
		int getWidth() const { return m_textWidth; }

		/// <summary>
		/// Visszaadja a generált szöveg magasságát pixelben.
		/// </summary>
		int getHeight() const { return m_textHeight; }
	};

	/// <summary>
	/// Lekérdezi, hogy érkezett-e leállítási (kilépési) kérelem a rendszertől.
	/// </summary>
	static bool isShutdownRequested() { return shutdownRequestedFlag; }

	/// <summary>
	/// Beállítja a renderelő aktuális rajzolási színét.
	/// </summary>
	static void setRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	/// <summary>
	/// Kirajzol egy üres téglalap körvonalat lebegőpontos koordinátákkal.
	/// </summary>
	static void renderDrawRectF(const Rect<float>& rect);

	/// <summary>
	/// Kirajzol egy kitöltött téglalapot lebegőpontos koordinátákkal.
	/// </summary>
	static void renderFillRectF(const Rect<float>& rect);

	/// <summary>
	/// A képernyő egy megadott területére másol (kirajzol) egy textúra-részletet.
	/// </summary>
	static void renderCopy(const Texture& texture, Rect<int>& srcRect, Rect<int>& dstRect);

	/// <summary>
	/// Letisztítja az aktuális renderelési felületet.
	/// </summary>
	static void renderClear();

	/// <summary>
	/// Megjeleníti az eddig renderelt tartalmat a képernyőn (buffer csere).
	/// </summary>
	static void renderPresent();

	/// <summary>
	/// Feldolgozza az ablak- és billentyűzet-eseményeket, majd frissíti a kontrollert.
	/// </summary>
	static void handleEvents(Controller& controller);

	/// <summary>
	/// Kirajzol egy tetszőleges szöveget vetett árnyékkal, opcionálisan középre igazítva.
	/// </summary>
	static void renderTextWithShadow(const Font& font, const char* string, const Color& color, Rect<int> dstRect, bool centerX = false);
};
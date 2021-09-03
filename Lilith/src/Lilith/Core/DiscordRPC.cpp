#include "lipch.h"
#include "DiscordRPC.h"

// doesnt work, pls fix <3

namespace Lilith {

	DiscordRPC::DiscordRPC()
	{
        /*DiscordState state{};

        discord::Core* core{};
        auto result = discord::Core::Create(883330272249147403, DiscordCreateFlags_Default, &core);
        state.core.reset(core);
        if (!state.core) {
            std::cout << "Failed to instantiate discord core! (err " << static_cast<int>(result)
                << ")\n";
            std::exit(-1);
        }

        state.core->SetLogHook(
            discord::LogLevel::Debug, [](discord::LogLevel level, const char* message) {
            LI_CORE_INFO("Log({0}): {1}", static_cast<uint32_t>(level), message);
        });

        discord::Activity activity{};
        activity.SetDetails("Fruit Tarts");
        activity.SetState("Pop Snacks");
        activity.GetAssets().SetSmallImage("the");
        activity.GetAssets().SetSmallText("i mage");
        activity.GetAssets().SetLargeImage("the");
        activity.GetAssets().SetLargeText("u mage");
        activity.SetType(discord::ActivityType::Playing);
        state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
            std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed")
                << " updating activity!\n";
        }); */
	}

	DiscordRPC::~DiscordRPC()
	{

	}
}
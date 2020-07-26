// Coypright Markus Ort - All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ButtonLabelProjectTarget : TargetRules
{
	public ButtonLabelProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ButtonLabelProject" } );
	}
}

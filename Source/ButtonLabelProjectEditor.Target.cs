// Coypright Markus Ort - All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ButtonLabelProjectEditorTarget : TargetRules
{
	public ButtonLabelProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ButtonLabelProject" } );
	}
}

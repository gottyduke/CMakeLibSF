#include "RE/B/BGSKeywordForm.h"
#include "RE/B/BGSFormFolderKeywordList.h"
#include "RE/B/BGSKeyword.h"

namespace RE
{
	bool BGSKeywordForm::ContainsKeywordString(std::string_view a_editorID)
	{
		bool result{};
		ForEachKeyword([&](const BGSKeyword* a_keyword) {
			if (result = a_keyword->formEditorID.contains(a_editorID); result) {
				return BSContainer::ForEachResult::kStop;
			}
			return BSContainer::ForEachResult::kContinue;
		});
		return result;
	}

	void BGSKeywordForm::ForEachKeyword(std::function<BSContainer::ForEachResult(BGSKeyword*)> a_callback)
	{
		for (const auto& keyword : keywords) {
			if (keyword && a_callback(keyword) == BSContainer::ForEachResult::kStop) {
				return;
			}
		}
		for (const auto& formFolderKeywordList : formFolderKeywordLists) {
			if (formFolderKeywordList) {
				for (const auto& keyword : formFolderKeywordList->keywords) {
					if (keyword && a_callback(keyword) == BSContainer::ForEachResult::kStop) {
						return;
					}
				}
			}
		}
	}

	std::uint32_t BGSKeywordForm::GetNumKeywords() const
	{
		return keywords.size();
	}

	bool BGSKeywordForm::HasKeywordString(std::string_view a_editorID)
	{
		bool result{};
		ForEachKeyword([&](const BGSKeyword* a_keyword) {
			if (result = (a_keyword->formEditorID == a_editorID); result) {
				return BSContainer::ForEachResult::kStop;
			}
			return BSContainer::ForEachResult::kContinue;
		});
		return result;
	}
}

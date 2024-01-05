// Copyright (c) 2024 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=4a9ae17508040a9f987bb8a939f99ace0df00c6f$
//

#ifndef CEF_LIBCEF_DLL_CTOCPP_VIEWS_MENU_BUTTON_CTOCPP_H_
#define CEF_LIBCEF_DLL_CTOCPP_VIEWS_MENU_BUTTON_CTOCPP_H_
#pragma once

#if !defined(WRAPPING_CEF_SHARED)
#error This file can be included wrapper-side only
#endif

#include "include/capi/views/cef_menu_button_capi.h"
#include "include/views/cef_menu_button.h"
#include "libcef_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefMenuButtonCToCpp : public CefCToCppRefCounted<CefMenuButtonCToCpp,
                                                       CefMenuButton,
                                                       cef_menu_button_t> {
 public:
  CefMenuButtonCToCpp();
  virtual ~CefMenuButtonCToCpp();

  // CefMenuButton methods.
  void ShowMenu(CefRefPtr<CefMenuModel> menu_model,
                const CefPoint& screen_point,
                cef_menu_anchor_position_t anchor_position) override;
  void TriggerMenu() override;

  // CefLabelButton methods.
  CefRefPtr<CefMenuButton> AsMenuButton() override;
  void SetText(const CefString& text) override;
  CefString GetText() override;
  void SetImage(cef_button_state_t button_state,
                CefRefPtr<CefImage> image) override;
  CefRefPtr<CefImage> GetImage(cef_button_state_t button_state) override;
  void SetTextColor(cef_button_state_t for_state, cef_color_t color) override;
  void SetEnabledTextColors(cef_color_t color) override;
  void SetFontList(const CefString& font_list) override;
  void SetHorizontalAlignment(cef_horizontal_alignment_t alignment) override;
  void SetMinimumSize(const CefSize& size) override;
  void SetMaximumSize(const CefSize& size) override;

  // CefButton methods.
  CefRefPtr<CefLabelButton> AsLabelButton() override;
  void SetState(cef_button_state_t state) override;
  cef_button_state_t GetState() override;
  void SetInkDropEnabled(bool enabled) override;
  void SetTooltipText(const CefString& tooltip_text) override;
  void SetAccessibleName(const CefString& name) override;

  // CefView methods.
  CefRefPtr<CefBrowserView> AsBrowserView() override;
  CefRefPtr<CefButton> AsButton() override;
  CefRefPtr<CefPanel> AsPanel() override;
  CefRefPtr<CefScrollView> AsScrollView() override;
  CefRefPtr<CefTextfield> AsTextfield() override;
  CefString GetTypeString() override;
  CefString ToString(bool include_children) override;
  bool IsValid() override;
  bool IsAttached() override;
  bool IsSame(CefRefPtr<CefView> that) override;
  CefRefPtr<CefViewDelegate> GetDelegate() override;
  CefRefPtr<CefWindow> GetWindow() override;
  int GetID() override;
  void SetID(int id) override;
  int GetGroupID() override;
  void SetGroupID(int group_id) override;
  CefRefPtr<CefView> GetParentView() override;
  CefRefPtr<CefView> GetViewForID(int id) override;
  void SetBounds(const CefRect& bounds) override;
  CefRect GetBounds() override;
  CefRect GetBoundsInScreen() override;
  void SetSize(const CefSize& size) override;
  CefSize GetSize() override;
  void SetPosition(const CefPoint& position) override;
  CefPoint GetPosition() override;
  void SetInsets(const CefInsets& insets) override;
  CefInsets GetInsets() override;
  CefSize GetPreferredSize() override;
  void SizeToPreferredSize() override;
  CefSize GetMinimumSize() override;
  CefSize GetMaximumSize() override;
  int GetHeightForWidth(int width) override;
  void InvalidateLayout() override;
  void SetVisible(bool visible) override;
  bool IsVisible() override;
  bool IsDrawn() override;
  void SetEnabled(bool enabled) override;
  bool IsEnabled() override;
  void SetFocusable(bool focusable) override;
  bool IsFocusable() override;
  bool IsAccessibilityFocusable() override;
  void RequestFocus() override;
  void SetBackgroundColor(cef_color_t color) override;
  cef_color_t GetBackgroundColor() override;
  bool ConvertPointToScreen(CefPoint& point) override;
  bool ConvertPointFromScreen(CefPoint& point) override;
  bool ConvertPointToWindow(CefPoint& point) override;
  bool ConvertPointFromWindow(CefPoint& point) override;
  bool ConvertPointToView(CefRefPtr<CefView> view, CefPoint& point) override;
  bool ConvertPointFromView(CefRefPtr<CefView> view, CefPoint& point) override;
};

#endif  // CEF_LIBCEF_DLL_CTOCPP_VIEWS_MENU_BUTTON_CTOCPP_H_

# AZERTY layout for Quark Plus from Checkerboards
<img src="https://avatars.githubusercontent.com/u/31043916" alt="" size="32" height="25" width="25" style="border-radius: 50%; vertical-align: middle;"> By [Steuv1871](https://github.com/Steuv1871)

![AZERTY layout for Quark Plus from Checkerboards](https://raw.githubusercontent.com/Steuv1871/penkesu/master/gallery/blog/quark.v2.top.jpg)
AZERTY layout with 2 rotary encodeur

Make example for this keyboard (after setting up your build environment):

    make checkerboards/quark_plus:steuv1871

# Features
- AZERTY layout
- Easily accessible specials characters used for programming
- Backspace become Delete with shift (to ease multiple keystrokes with stiff rotary encoders)
- Alt+Tab on rotary encoders
- Interpuct macro for inclusive writting
- *(optionnal)* Fourth layer for gaming (you need to rename 'keymap_gamelayer.c' in 'keymap.c' to enable it)

# Layout
![AZERTY layout for Quark Plus layout](https://raw.githubusercontent.com/Steuv1871/penkesu/master/gallery/blog/quark.v2.layout_full.png)

## Rotary encoder actions
* **AZERTY Layer**
    - **Left encoder:** Mouse wheel
    - **Right encoder:** Home / End
* **Lower Layer**
    - **Left encoder:** Up / Down arrow
    - **Right encoder:** Alt+Tab
* **Raise Layer**
    - **Left encoder:** Page Up / Page Down
    - **Right encoder:** Control Left / Control Right (Next/Previous word)
* **Func Layer**
    - **Left encoder:** RGB Mod
    - **Right encoder:** Volume Up / Volume Down

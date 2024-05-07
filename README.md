<img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/920682e3-8251-4aa4-8d89-87a1efc0a0ee" width="100%" height="100%" title="Banner" alt="Banner"></img><br/>
# <img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/aab331c7-e5fa-4e8e-8829-8821eea97b8e" width="4.5%" height="4.5%" title="Icon" alt="Icon"></img> Copycat's CookieRun

> Windows API를 활용한 2D Game Copy Project

<a href="https://www.notion.so/Copycat-s-CookieRun-ea8a5923a4724a6db10cb8c8b85e599f?pvs=4" target="_blank"><img src="https://img.shields.io/badge/Notion%EC%9D%84%20%ED%86%B5%ED%95%B4%20%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B3%BC%EC%A0%95%20%ED%99%95%EC%9D%B8%ED%95%98%EA%B8%B0-222222?style=social&logo=Notion&logoColor=Black&label=Notion&logoSize=200"/></a>

<br>

### 목차
- [프로젝트 개요](#프로젝트-개요)
- [프로젝트 설명](#프로젝트-설명)
- [프로젝트 결과](#프로젝트-결과)

<br><br><br>

### 프로젝트 개요
<br>


<!-- 아래 표에는 넓이를 위한 전각문자가 포함되어 있음 (　)-->

<div align="center">

| 개요 | 설명 |
| :--- | :--- |
|  📋 프로젝트 이름   | Copycat’s CookieRun 　　　　　　　　　　　　 |
|  🗓️ 프로젝트 기간   | 2024.03-2024.04 |
|  🛠️ 개발 환경 및 언어    　　　　　　　　　　　| C++ <br>Windows API <br>Visual Studio 2022 |
| 👥 멤버             | 김주향 @jjudy  |

</div>
  
```
2013년 출시된 쿠키런의 모작으로, C++, Windows API를 활용해 제작했습니다.

개발자는 Edit Mode에서 제공되는 툴을 통해서 Stage의 장애물이나 아이템들을 직접 배치할 수 있고,
Atlas Texture를 가져와 애니메이션을 제작할 수 있습니다.
MFC를 사용한 직관적인 인터페이스를 통해 편의성과 확장성을 증가시켰습니다.
```

<br><br><br>

### 프로젝트 설명

<br>

**게임 설명**

<div align="center">
<img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/4294edb2-ff76-42b3-b3aa-c7c9dd476f5e" width="256px" height="256px" title="Logo" alt="Logo"></img><br/>
<img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/7c334442-00af-44e4-bbaa-ffb308442e5c" width="226px" height="110px" title="Title" alt="Title"></img><br/>
</div>




<!-- 아래 표에는 넓이를 위한 전각문자가 포함되어 있음 (　)-->
<div align="center">
    
| 개요 | 설명 |
| :--- | :--- |
|  게임명   | 쿠키런　　　　　　　　　　 |
|  개발사 / 출시일   | 데브시스터즈 (現 스튜디오 킹덤) / 2013년 4월 2일 |
|  플랫폼 | 모바일 (Andriod \| iOS) |
| 장르 | 횡스크롤 러닝 액션  |

</div>

<br><br>

**프로젝트에 반영된 게임의 특징**
<br><br>

- 게임 플레이 및 메커니즘 <br><br>
    쿠키런은 **점프**와 **슬라이드**로 조작을 하며, 스크린의 장애물들을 피해 달리면서 젤리를 획득함으로써 점수를 올리는 게임입니다.   
    체력 시스템은 쿠키가 달리는 동안 체력이 일정량씩 깎이거나, 장애물에 부딪힐 경우 데미지를 받게 됩니다. 체력이 모두 소진되는 경우와 구멍에 떨어져 낙사하게 되는 경우 게임이 종료됩니다.

<br>

- 캐릭터 <br><br>
    게임 플레이에 사용되는 캐릭터는 **쿠키**와 **펫**이 있습니다. 
    쿠키와 펫은 여러 종류 중 하나를 선택해 플레이할 수 있으며, 플레이 시마다 변경할 수 있습니다.
    
<br>

- 스테이지 <br><br>
    메인 **에피소드**는 총 5개이며, 한 에피소드에는 여러 개의 **스테이지**가 존재합니다. 스테이지 끝마다 생명 물약이 배치되어 있으며, 이 생명 물약을 전후로 스테이지가 나뉘고 배경이나 장애물이 달라집니다. (장애물들의 유형은 동일, 이미지 에셋만 변경)

<br>

- 젤리 및 아이템 <br><br>
    여러 종류의 젤리를 획득할 수 있으며, 젤리의 유형마다 획득하는 점수가 다르게 적용됩니다. 또, 다양한 코인 유형의 젤리를 통해 코인 재화를 획득할 수 있습니다.
    아이템 젤리의 종류는 고속화, 거대화, 자력 아이템이 있으며 아이템을 획득할 경우 일정시간 동안 캐릭터인 쿠키 및 펫에게 효과가 적용됩니다.
    젤리 중 알파벳 젤리의 B, O, N, U, S, T, I, M, E 9종류를 모을 수 있으며 획득한 알파벳은 UI에 표시됩니다.

<br><br><br>

**프로젝트 설명** <br><br>

> 🛠️ **손쉽게 Stage, Animation 제작이 가능한 Edit Tool**

<br>

- Animation Edit Tool

    | Mode | Animation Edit Mode |
    | --- | :---: |  
    | 구현 | <img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/6b0f4912-c518-480b-ad87-2f497d809d9c" width="85%" height="85%" title="Animation Edit Mode" alt="AnimationEditMode"></img><br/> |
    | 개요 | 게임에 활용되는 애니메이션 에셋을 직접 생성하고 편집할 수 있는 Animation Edit Mode |
    | 세부<br>기능 | - Atlas Texture를 활용해 직접 애니메이션 에셋 제작 가능<br>- 마우스 드래그를 활용한 Direct Draw / Spin Control을 활용한 세부 수치 조정을 통해<br>원하는 애니메이션 프레임을 손쉽게 편집 가능<br>- Play / Stop을 통해 현재 편집 중인 애니메이션 미리보기 가능<br>- 파일 스트림을 통한 저장 / 불러오기 |

<br>

- Stage Edit Tool

| Mode | Static Object Edit Mode | Dynamic Object Edit Mode |
| --- | :---: | :---: |
| 구현 | <img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/d30e1a0a-1738-4eff-b693-e3c2b63067da" width="100%" height="100%" title="Static Object Edit Mode" alt="STObjEditMode"></img><br/> | <img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/38f22a6c-26f0-4375-881d-859486db38ea" width="100%" height="100%" title="Dynamic Object Edit Mode" alt="DNObjEditMode"></img><br/> |
| 개요 | 맵을 구성하는 Platform과 Obstacle 등의 에피소드/스테이지별 알맞은 에셋에 따른 Spawn Position을 지정할 수 있는 모드 | 게임을 진행하며 스테이지에서 획득할 수 있는 유동적인 오브젝트들의 Spawn Position을 지정할 수 있는 모드 |
| 세부<br>기능 | - 각 Stage에 맞는 Object의 에셋과 Drag & Drop을 통한 편리한 위치 지정 가능 <br> - 각 Object의 배치 가능 위치에 따라 가이드라인 생성 & 배치 시 Position 조정 <br> - 배치한 Static Object의 세부적인 Position을Button UI를 통해 조정 가능 | - Tile의 형태로 Jelly 및 Coin의 Spawn Position 저장 가능 <br> - 선택한 Object를 클릭/드래그 하는 타일의 위치에 배치 가능 |


<br><br>

> 🏆 **원작 ‘쿠키런’의 플레이 방식 / 컨텐츠를 재현**

<br>

- 조작 방식
    
    기본적인 UI는 모두 마우스 `L Click` 활용
    
    | 상호작용 | JUMP | SLIDE |
    | :---: | :---: | :---: |
    | 키보드 | SPACE BAR  | ⬇️ |

<br>

- 컨텐츠
        
    | 최고 점수 갱신 | 스테이지 |
    | :---: | :---: |
    | <img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/ed3fa2d5-a071-4546-adf2-d77a2a6f1347" width="100%" height="100%" title="Lobby" alt="Lobby"></img><br/> | <img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/b533cd92-67da-4f16-8ba9-3e70c37d132b" width="100%" height="100%" title="ChangeStage" alt="ChangeStage"></img><br/> |
    | 플레이어의 최고 점수 저장해 갱신 가능 | 여러 에피소드를 선택해 순차적으로 스테이지 플레이 가능 |

    <br>
  
    | 쿠키 | 펫 |
    | :---: | :---: |
    | <img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/812c5cfa-d51d-4cdb-8523-7f3339445ca2" width="100%" height="100%" title="SelectCookie" alt="SelectCookie"></img><br/> | <img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/5290933e-71ad-4504-9b78-051fdf46c17b" width="100%" height="100%" title="SelectPet" alt="SelectPet"></img><br/> |
    | 여러 종류의 쿠키들 중 선택해 플레이 가능 | 여러 종류의 펫들 중 선택해 플레이 가능 |

<br><br><br>

### 프로젝트 결과

<br>

**시연 영상** <br><br>
_이미지를 클릭하면 youtube링크로 이동합니다_

<div align="center">
<a href="https://youtu.be/xiwObELJPmY?si=NiR0zuokpjSpDYIH"><img src="https://github.com/jjudykim/WinAPI_2DGameProject_CopyCats-CookieRun/assets/66450769/3d1f30ba-be6a-4c7f-9f65-a337ffcd1b41" width="80%" height="80%" title="ResultVideo" alt="ResultVideo"></img></a>
</div>

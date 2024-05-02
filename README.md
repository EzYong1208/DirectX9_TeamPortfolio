DirectX SDK9 3D 게임 모작(팀 프로젝트) 입니다.
주요 역할 담당은 아이템과 NPC이고, 제가 담당했던 부분만 추려서 올렸습니다.

- 하나의 아이템 바운딩 박스 클래스를 통하여 다양한 아이템들을 불러오고 사용할 수 있도록 구현했습니다.
- 다양한 아이템 클래스들을 크게 오른손 무기, 왼손 무기, 장신구, 장비 4가지로 나누었고 그 타입에 따른 정보들을 설정하고 관리할 수 있게 구현했습니다.
- 아이템 생성 시 rand 함수를 이용해 나온 값에 따라 스위치 문을 이용해 여러 아이템 중 하나의 분기에 해당하는 아이템이 나올 수 있도록 구현했습니다.
- 특정 NPC와의 상호작용을 통하여 상점 기능을 이용할 수 있으며 물건 구입과 판매가 가능하게 구현했습니다.
- imgui로 만들어진 툴을 이용해 NPC와 아이템들을 배치하고 스테이지 생성 시 저장된 위치에서 불러올 수 있게끔 파일 입출력을 통해 세이브 파일을 만들어 불러오게 구현했습니다.

[![Video Label](http://img.youtube.com/vi/Di28Ud8U1IY/0.jpg)](https://youtu.be/Di28Ud8U1IY)
###### ▶ 위 이미지는 시연회 유튜브 링크입니다.
감사합니다.

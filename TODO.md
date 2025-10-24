# TODO - UE GAS 네트워크 포트폴리오

## 진행 상태 범례
- ✅ 완료
- 🔄 진행 중
- ⏳ 대기 중
- ❌ 보류/취소

---

## Phase 1: GAS 프레임워크 기본 구조 ✅

### 1.1 AbilitySystemComponent 설정 ✅
- ✅ PlayerState에 ASC 추가
- ✅ IAbilitySystemInterface 구현
- ✅ 네트워크 복제 설정 (DOREPLIFETIME)
- ✅ NetUpdateFrequency 최적화 (100Hz)

### 1.2 멀티플레이 초기화 로직 ✅
- ✅ PossessedBy 구현 (서버)
- ✅ OnRep_PlayerState 구현 (클라이언트)
- ✅ InitAbilityActorInfo 호출
- ✅ nullptr 안전 체크 추가

---

## Phase 2: AttributeSet 구현 ⏳

### 2.1 AttributeSet 클래스 생성
- ⏳ MyAttributeSet 클래스 생성
- ⏳ 기본 속성 정의
  - Health (체력)
  - MaxHealth (최대 체력)
  - Mana (마나)
  - MaxMana (최대 마나)
  - Stamina (스태미나)
  - MaxStamina (최대 스태미나)
- ⏳ 속성 복제 설정
- ⏳ 속성 변경 콜백 구현

### 2.2 AttributeSet을 PlayerState에 통합
- ⏳ PlayerState에 AttributeSet 추가
- ⏳ 생성자에서 AttributeSet 초기화
- ⏳ GetAttributeSet 함수 구현

---

## Phase 3: GameplayAbility 구현 ⏳

### 3.1 기본 Ability 클래스
- ⏳ MyGameplayAbility 베이스 클래스 생성
- ⏳ ActivateAbility 구현
- ⏳ EndAbility 구현
- ⏳ Ability 취소 로직

### 3.2 테스트용 Ability
- ⏳ 기본 공격 Ability (예: 펀치)
- ⏳ Animation Montage 연동 테스트
- ⏳ Cooldown 적용
- ⏳ Cost(Mana/Stamina) 적용

### 3.3 Ability 등록 및 부여
- ⏳ 캐릭터 생성 시 Ability 자동 부여
- ⏳ Ability 입력 바인딩 시스템

---

## Phase 4: GameplayEffect 구현 ⏳

### 4.1 기본 Effect
- ⏳ Instant Effect (즉시 적용)
- ⏳ Duration Effect (지속 시간)
- ⏳ Infinite Effect (무한 지속)

### 4.2 테스트용 Effect
- ⏳ 데미지 Effect
- ⏳ 힐 Effect
- ⏳ 버프/디버프 Effect

---

## Phase 5: Gameplay Tags 시스템 ⏳

### 5.1 Tag 구조 설계
- ⏳ 프로젝트 Tag 계층 구조 설계
  - Ability.Attack.Melee
  - Ability.Skill.Active
  - State.Dead
  - State.Stunned
  - etc.

### 5.2 Tag 설정
- ⏳ DefaultGameplayTags.ini 설정
- ⏳ C++에서 Native Tag 정의

---

## Phase 6: 입력 시스템 통합 ⏳

### 6.1 Enhanced Input 연동
- ⏳ Input Action 생성
- ⏳ Input Mapping Context 설정
- ⏳ Ability 입력 바인딩

### 6.2 Ability 활성화
- ⏳ 키 입력으로 Ability 실행
- ⏳ Ability Queue 시스템 (선택)

---

## Phase 7: UI 연동 ⏳

### 7.1 AttributeSet UI 바인딩
- ⏳ 체력바 Widget
- ⏳ 마나바 Widget
- ⏳ AttributeSet 변경 시 UI 업데이트

### 7.2 Ability UI
- ⏳ Cooldown 표시
- ⏳ Ability 아이콘 UI
- ⏳ Cost 표시

---

## Phase 8: 네트워크 테스트 및 최적화 ⏳

### 8.1 멀티플레이 테스트
- ⏳ 로컬 멀티플레이 테스트 (2-4 플레이어)
- ⏳ Dedicated Server 테스트
- ⏳ 복제 검증

### 8.2 최적화
- ⏳ 네트워크 프로파일링
- ⏳ Replication 모드 최적화
- ⏳ Bandwidth 최적화

---

## Phase 9: 고급 기능 (선택) ⏳

### 9.1 Gameplay Cue
- ⏳ 타격 이펙트
- ⏳ 스킬 이펙트
- ⏳ 사운드 통합

### 9.2 Ability Task
- ⏳ Custom Ability Task 구현
- ⏳ 비동기 작업 처리

### 9.3 Targeting System
- ⏳ Target Actor 구현
- ⏳ 범위 스킬 타겟팅

---

## Phase 10: 문서화 및 포트폴리오 준비 ⏳

### 10.1 코드 문서화
- ⏳ 주요 클래스 주석 추가
- ⏳ 함수 설명 추가
- ⏳ README 업데이트

### 10.2 포트폴리오 자료
- ⏳ 시연 영상 제작
- ⏳ 기능 설명 문서
- ⏳ 코드 하이라이트 정리

---

## 버그 및 이슈 트래킹

### 현재 이슈
_이슈 없음_

### 해결된 이슈
- ✅ ASC 초기화 타이밍 문제 (PostInitializeComponents → PossessedBy/OnRep_PlayerState)
- ✅ nullptr 크래시 방지 체크 추가

---

## 메모 및 아이디어

### 구현 아이디어
- 대시 스킬
- 이동 관련 Root Motion Ability
- 콤보 시스템
- 파티 시스템 (멀티플레이)

### 참고 사항
- GAS는 리플렉션 시스템을 많이 사용하므로 빌드 시간이 길 수 있음
- AttributeSet 변경 시 항상 PreAttributeChange/PostGameplayEffectExecute 사용
- 멀티플레이 테스트는 초기부터 자주 수행할 것

---

**최종 업데이트**: 2025-10-22
**다음 목표**: UI 시스템 구축 (체력바, 스킬 아이콘, 쿨다운 표시)

---

## 🎯 MMORPG 포트폴리오 로드맵

### ✅ 완료된 기능

#### 0. 콤보 공격 시스템 구현 ✅ (2025-01-24)
- ✅ **GA_MeleeAttack 콤보 시스템 추가**
  - 최대 3단 콤보 지원 (MaxComboCount = 3)
  - 콤보 리셋 타이머 (1.5초)
  - ComboMontages 배열로 각 콤보 단계별 애니메이션 관리
  - CurrentComboCount 자동 추적 및 리셋 로직
  - PlayComboMontage() / ResetCombo() 함수 구현
- ✅ **MeleeWeaponComponent 충돌체 제어 시스템**
  - EnableCollision() / DisableCollision() 함수 추가
  - HitActors 배열로 중복 피격 방지
  - 캡슐 컴포넌트(HitCapsule) 기반 충돌 감지
  - 충돌체 활성화 상태 관리 (bIsAttacking)
- ✅ **AnimNotify_WeaponCollision 클래스 생성**
  - 애니메이션 노티파이로 무기 충돌체 ON/OFF 제어
  - bEnableCollision 플래그로 타이밍 정밀 제어
  - 애니메이션 프레임에서 공격 판정 시작/종료 관리
  - 파일 위치: `Source/UE_GAS_Net_PortFolio/AnimNotify/`
- ✅ **캐릭터 구조 리팩토링**
  - MyCharacterBase: 무기 컴포넌트 제거 (공통 기능만 유지)
  - MyPlayer: 카메라, 컨트롤러 등 플레이어 공통 기능
  - **AuroraPlayer 클래스 추가**: 근접 무기(칼) 전용 캐릭터
    - MeleeWeaponComponent 추가
    - "weapon" 소켓에 무기 부착
    - 파일: `Source/UE_GAS_Net_PortFolio/Character/AuroraPlayer.h/cpp`
- ✅ **입력 시스템 - 마우스 왼쪽 클릭**
  - MyPlayerController에 MainAction 추가
  - OnMainAction() 콜백으로 슬롯 1번 Ability 실행
  - Enhanced Input System 사용

#### 1. 프로젝트 빌드 수정 및 최적화 ✅ (2025-10-22)
- ✅ BOM (Byte Order Mark) 제거 - 모든 소스 파일 (.h, .cpp)
- ✅ Build.cs 파일 정리
  - 중복 모듈 제거 (GameplayTasks, Niagara, GameplayAbilities, GameplayTags)
  - Public/Private 모듈 분류 최적화
- ✅ GameplayAbilities 헤더 파일 추가
  - MyPlayerState.h: GameplayAbilitySpec.h
  - MyAttributeSet.h: GameplayEffectExtension.h
  - MyGameplayAbility.h: GameplayTagContainer.h
  - MyPlayerController.h: AbilitySystemInterface.h
  - MyCharacterBase.h: AbilitySystemInterface.h
- ✅ MyEnemy AbilitySystemComponent 구현
  - IAbilitySystemInterface 상속
  - ASC 및 AttributeSet 추가
  - 네트워크 복제 설정 (Minimal 모드)

#### 1. PlayerController 타겟팅 시스템 ✅
- ✅ CurrentTarget 변수 및 네트워크 복제
- ✅ FindNearestEnemy() - 30m 반경, 180도 시야각
- ✅ Tab 키 타겟팅
- ✅ Server RPC를 통한 타겟 동기화
- ✅ Enemy 태그 기반 타겟 필터링
- ✅ **타겟 락온 카메라 시스템** (2025-10-22)
  - 카메라가 타겟을 자동으로 추적
  - 캐릭터 몸체도 타겟 방향으로 회전
  - 부드러운 보간 (Camera: 10.0, Character: 8.0)
  - Pitch 각도 제한 (-45° ~ 45°)
  - 자동 타겟 해제 (거리 50m 이상, 타겟 사망)
- ✅ **타겟 토글 기능 개선** (2025-10-22)
  - Tab 키로 락온/해제 토글
  - 락온 해제 시 캐릭터 회전 모드 복구
  - bOrientRotationToMovement 자동 전환

#### 2. Enhanced Input 시스템 통합 ✅
- ✅ PlayerController로 모든 입력 통합
- ✅ Mapping Context 관리
- ✅ 이동/시점/점프/달리기 입력 처리
- ✅ Ability 1~6 입력 바인딩

#### 3. GAS 스킬 시스템 기본 구조 ✅
- ✅ MyGameplayAbility 베이스 클래스
  - 코스트 체크 (마나/스태미나)
  - 타겟 획득 및 거리 체크
  - Helper 함수 (GetASC, GetAttributeSet 등)
- ✅ GA_MeleeAttack (첫 번째 스킬)
  - 근접 공격 (2m 사거리)
  - 스태미나 10 소모
  - 데미지 계산 (AttackPower + BaseDamage - Defense)
- ✅ PlayerState Ability 부여 시스템
  - DefaultAbilities 배열
  - GrantAbilities() / RemoveAbilities()
- ✅ PlayerController Ability 활성화
  - ActivateAbilityBySlot(1~6)
  - 슬롯 번호로 Ability 찾아서 실행

### 🔄 진행 중

#### 4. 추가 스킬 구현 (5개)
- ⏳ GA_HeavyStrike - 강공격 (2번 키)
- ⏳ GA_HealingWave - 힐 스킬 (3번 키)
- ⏳ GA_AoEBlast - 범위 공격 (4번 키)
- ⏳ GA_Haste - 이동속도 버프 (5번 키)
- ⏳ GA_Ultimate - 궁극기 (6번 키)

### ⏳ 예정된 작업

#### 4.1 콤보 공격 시스템 - 언리얼 에디터 설정 ⏳
- ⏳ **Input Action 설정**
  - IA_MainAction Input Action 생성
  - Input Mapping Context에 왼쪽 마우스 버튼 매핑
  - BP_MyPlayerController에서 MainAction 할당
- ⏳ **애니메이션 몽타주 설정**
  - Primary_Attack_A_Montage (1타) 생성
  - Primary_Attack_B_Montage (2타) 생성
  - Primary_Attack_C_Montage (3타) 생성
  - BP_GA_MeleeAttack에서 ComboMontages 배열에 할당
- ⏳ **애니메이션 노티파이 배치**
  - 각 콤보 몽타주에 AnimNotify_WeaponCollision 추가
  - 공격 시작 프레임: bEnableCollision = true
  - 공격 종료 프레임: bEnableCollision = false
- ⏳ **스켈레탈 메시 소켓 설정**
  - Aurora 스켈레탈 메시에 "weapon" 소켓 생성
  - 손 본에 소켓 부착
  - 소켓 위치/회전 조정
- ⏳ **MeleeWeaponComponent 설정**
  - BP_Aurora에서 MeleeWeapon 컴포넌트 확인
  - HitCapsule 크기 조정 (CapsuleRadius, CapsuleHalfHeight)
  - 디버그용 충돌체 시각화 활성화

#### 5. GameplayEffect 시스템
- ⏳ GE_Cooldown - 쿨다운 Effect
- ⏳ GE_Cost - 코스트 Effect
- ⏳ GE_Damage - 데미지 Effect

#### 6. 파티 시스템
- ⏳ PartyManager (GameState)
- ⏳ 파티 초대/수락/거절
- ⏳ 파티원 UI (체력/마나바)
- ⏳ 파티 버프 공유

#### 7. AI Boss
- ⏳ MyAIController 구현
- ⏳ Behavior Tree
- ⏳ 페이즈 전환 (50% HP)
- ⏳ 패턴 공격

#### 8. 전투 UI
- ⏳ HUD (체력/마나/스태미나바)
- ⏳ 스킬바 (쿨다운 표시)
- ⏳ 타겟 프레임
- ⏳ 파티 프레임
- ⏳ Floating Combat Text

#### 9. 네트워크 테스트
- ⏳ 4인 파티 테스트
- ⏳ Dedicated Server
- ⏳ 최적화

---

## 📂 주요 파일 구조

```
Source/UE_GAS_Net_PortFolio/
├── Ability/
│   ├── GA_MeleeAttack.h/cpp       # 콤보 공격 Ability (3단 콤보)
│   └── MyGameplayAbility.h/cpp    # Ability 베이스 클래스
├── AnimNotify/
│   └── AnimNotify_WeaponCollision.h/cpp  # 무기 충돌 노티파이
├── Character/
│   ├── MyCharacterBase.h/cpp      # 공통 캐릭터 기능
│   ├── MyPlayer.h/cpp             # 공통 플레이어 기능
│   ├── AuroraPlayer.h/cpp         # 근접 무기 캐릭터 ⚔️
│   ├── MyEnemy.h/cpp              # 적 캐릭터
│   └── MyBoss.h/cpp               # 보스 캐릭터
├── Controller/
│   ├── MyPlayerController.h/cpp   # 입력 처리 (MainAction, 타겟팅)
│   └── MyAIController.h/cpp       # AI 컨트롤러
├── PlayerState/
│   └── MyPlayerState.h/cpp        # ASC 및 AttributeSet 관리
├── AttributeSet/
│   └── MyAttributeSet.h/cpp       # 속성 관리 (HP, MP, Stamina 등)
└── Weapon/
    ├── WeaponComponent.h/cpp      # 무기 베이스 클래스
    └── MeleeWeaponComponent.h/cpp # 근접 무기 컴포넌트
```

---

## 💡 콤보 공격 시스템 작동 방식

### 1. 콤보 입력 흐름
```
왼쪽 마우스 클릭
  ↓
OnMainAction() (MyPlayerController)
  ↓
ActivateAbilityBySlot(1)
  ↓
GA_MeleeAttack::ActivateAbility()
  ↓
CurrentComboCount++ (1→2→3→1...)
  ↓
PlayComboMontage()
  ↓
ComboMontages[CurrentComboCount-1] 재생
```

### 2. 콤보 타이밍 관리
- 1.5초 안에 다음 클릭 → 콤보 이어짐
- 1.5초 경과 → ResetCombo() 호출 (CurrentComboCount = 0)
- FTimerHandle로 타이머 관리

### 3. 무기 충돌 작동 방식
```
애니메이션 재생
  ↓
AnimNotify_WeaponCollision (bEnableCollision = true)
  ↓
MeleeWeapon->EnableCollision()
  ↓
HitCapsule 충돌 활성화
  ↓
OnHitCapsuleBeginOverlap() - 충돌 감지
  ↓
HitActors 배열 체크 (중복 피격 방지)
  ↓
데미지 적용
  ↓
AnimNotify_WeaponCollision (bEnableCollision = false)
  ↓
DisableCollision()
```

---

## 🐛 알려진 이슈
_현재 이슈 없음_

---

## 📝 참고 사항

### 콤보 시스템
- ComboMontages 배열은 블루프린트에서 설정 필요
- 애니메이션 몽타주에 노티파이 배치 필수
- 콤보 리셋 시간은 ComboResetTime 변수로 조정 가능

### 무기 충돌 시스템
- HitCapsule 크기는 무기에 맞게 조정 필요
- weapon 소켓 위치가 정확해야 충돌 판정이 정상 작동
- bIsAttacking 플래그로 충돌 활성화 상태 관리

### 캐릭터 확장
- 총 쏘는 캐릭터는 MyPlayer 상속 + RangedWeaponComponent 추가
- 각 캐릭터 타입별로 고유한 무기 컴포넌트 사용

---

**최종 업데이트**: 2025-01-24
**최신 커밋**: 9b17e27 - "feat: Implement combo attack system with animation notify"
**다음 목표**: 언리얼 에디터에서 콤보 애니메이션 몽타주 설정 및 노티파이 배치

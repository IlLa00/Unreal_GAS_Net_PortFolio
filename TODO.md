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

#### 0. 프로젝트 빌드 수정 및 최적화 ✅ (2025-10-22)
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
